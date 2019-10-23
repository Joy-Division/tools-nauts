/*
 * POLICENAUTS Toolbox
 * DPK File Extractor
 *
 * Jonathan Ingram (2017～2019)
 * Special thanks to Missingno_force
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define PATH_CHAR_LIMIT 260

/*---------------------------------------------------------------------------*/

#include "cmtypes.h"
#include "cmswap.h"
#include "cmutil.h"

#include "dpk_extract.h"
#include "fmt_data_dpk.h"

static DPK_HEADER DpkHeader;
static DPK_ENTRY  DpkEntry;

static bool DpkEndianFlag;

/*---------------------------------------------------------------------------*
 * DPK Header
 *---------------------------------------------------------------------------*/

void DPK_LoadHeader( FILE *dpk )
{
	fseek( dpk, 0, SEEK_SET );
	fread( &DpkHeader, sizeof(DPK_HEADER), 1, dpk );
}

void DPK_ReverseHeader( void )
{
	CM_ByteSwap32R( &DpkHeader.block_size );
	CM_ByteSwap32R( &DpkHeader.file_count );
	CM_ByteSwap32R( &DpkHeader.entry_end );
	CM_ByteSwap32R( &DpkHeader.entry_size );
}

/*---------------------------------------------------------------------------*
 * DPK Entry Table
 *---------------------------------------------------------------------------*/

void DPK_LoadEntry( FILE *dpk, int filenum )
{
	uint32 seekpos = (sizeof(DPK_HEADER) + (sizeof(DPK_ENTRY) * filenum));
	
	fseek( dpk, seekpos, SEEK_SET );
	fread( &DpkEntry, sizeof(DPK_ENTRY), 1, dpk );
}

void DPK_ReverseEntry( void )
{
	CM_ByteSwap32R( &DpkEntry.offset );
	CM_ByteSwap32R( &DpkEntry.length );
	CM_ByteSwap32R( &DpkEntry.checksum );
}

/*---------------------------------------------------------------------------*
 * DPK Integrity Check
 *---------------------------------------------------------------------------*/

bool DPK_CheckID( void )
{
	if (( DpkHeader.formatID != 'DIRF' )  // 'FRID' check (LE)
	&&  ( DpkHeader.formatID != 'FRID' )) // 'DIRF' check (BE)
	{
		printf( "\nInvalid format ID!!\n" );
		return false;
	}
	printf( "\nFormat ID  : %.4s ", (char *)&DpkHeader.formatID );
	return true;
}

bool DPK_CheckAttribute( void )
{
	if ( DpkHeader.attribute == DPK_ATTR_LE ){
		DpkEndianFlag = false;
		printf( "(Little Endian)\n" );
		return true;
	}
	else if ( DpkHeader.attribute == DPK_ATTR_BE ){
		DpkEndianFlag = true;
		printf( "(Big Endian)\n" );
		return true;
	} else {
		printf( "\nInvalid endian signature!!\n" );
		return false;
	}
}

/*---------------------------------------------------------------------------*
 * DPK File Extract
 *---------------------------------------------------------------------------*/

bool DPK_CreateOutputDir( char *dir, char *arg )
{
	// copy filename
	strcpy( dir, arg );
	// remove extension
	*strrchr( dir, '.' ) = 0;
	
	printf( "\nOutput Directory: %s\n", dir );
	
	if ( CM_MakeDir( dir ) < 0 ){
		printf( "Could not create %s !!\n", dir );
		return false;
	}
	return true;
}

bool DPK_ExtractFile( FILE *dpk, FILE *out, char *name, char *dir )
{
	snprintf( name, PATH_CHAR_LIMIT, "%s/%s", dir, DpkEntry.name );
	
	// error check
	if ( !(out = fopen( name, "wb" ))){
		printf( "Could not create %s !!\n", name );
		fclose( out );
		return false;
	}
	
	char *buffer = malloc( DpkEntry.length );
	
	fseek( dpk, DpkEntry.offset, SEEK_SET );
	fread( buffer, DpkEntry.length, 1, dpk );
	fwrite( buffer, 1, DpkEntry.length, out );
	
	// cleanup
	fclose( out );
	free( buffer );
	return true;
}

/*---------------------------------------------------------------------------*
 * Program Control Flow
 *---------------------------------------------------------------------------*/

int main( int argc, char **argv )
{
	FILE *fin, *fout;
	char fout_name[ PATH_CHAR_LIMIT ] = "";
	
	// error check
	if ( argc != 2 ){
		printf( "Wrong number of arguments.\n" );
		printf( "Use: %s example.dpk\n", argv[0] );
		goto cleanup_exit;
	}
	if ( !(fin = fopen( argv[1], "rb" ))){
		printf( "Could not open %s !!\n", argv[1] );
		goto cleanup_exit;
	}
	
	// extension check
	char *argv1_ext = strrchr( argv[1], '.' );
	if ( !argv1_ext ) goto ext_error;
	
	if ( ( strcmp( argv1_ext, ".dpk" ) )
	&&   ( strcmp( argv1_ext, ".DPK" ) ) ){
ext_error:
		printf( "The filename must end with \".dpk\" or \".DPK\"\n" );
		goto cleanup_fclose;
	}
	
	DPK_LoadHeader( fin );
	
	// header error check
	if ( !DPK_CheckID() || !DPK_CheckAttribute() )
		goto cleanup_fclose;
	
	if ( DpkEndianFlag )
		DPK_ReverseHeader();
	
//	printf( "Format ID  : %.4s\n", (char *)&DpkHeader.formatID );
	printf( "Attribute  : %08x\n", DpkHeader.attribute );
	printf( "Block Size : %08x\n", DpkHeader.block_size );
	printf( "File Count : %d\n",   DpkHeader.file_count );
	printf( "Entry End  : %08x\n", DpkHeader.entry_end );
	printf( "Entry Size : %08x\n", DpkHeader.entry_size );
	
	char *outdir = malloc( strlen(argv[1])+1 ); // +1 for NULL char
	
	if ( !DPK_CreateOutputDir( outdir, argv[1] ) )
		goto cleanup_free;
	
	printf( "\n%-12s %-8s %-8s %-8s\n", "Name", "Offset", "Length", "Checksum" );
	printf( "---------------------------------------\n" );
	
	for ( int i=0 ; i < DpkHeader.file_count ; i++ )
	{
		DPK_LoadEntry( fin, i );
		
		if ( DpkEndianFlag )
			DPK_ReverseEntry();
		
		printf( "%-12s %08x %08x %08x\n",
			DpkEntry.name,
			DpkEntry.offset,
			DpkEntry.length,
			DpkEntry.checksum );
		
		if ( !DPK_ExtractFile( fin, fout, fout_name, outdir ) )
			goto cleanup_free;
	}
	
cleanup_free:
	free( outdir );
cleanup_fclose:
	fclose( fin );
cleanup_exit:
	printf( "\n***** Program Exit *****\n" );
	return 0;
}

/*---------------------------------------------------------------------------*
 * END OF FILE
 *---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: c; -*- */
/* vim: set noet ts=4 sw=4 ft=c ff=dos fenc=utf-8 : */
