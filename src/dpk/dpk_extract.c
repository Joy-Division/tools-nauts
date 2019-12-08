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

#include "cmdefs.h"
#include "cmtypes.h"
#include "cmswap.h"
#include "cmutil.h"
#include "shared.h"

#define MAX_PATH_CHAR 260

/*---------------------------------------------------------------------------*/

#include "dpk_extract.h"
#include "fmt_data.h"

static bool dpkEndianFlag;

/*---------------------------------------------------------------------------*
 * DPK Header
 *---------------------------------------------------------------------------*/
void DPK_LoadHeader( DPK_HEADER *head, FILE *dpk )
{
	fseek( dpk, 0, SEEK_SET );
	fread( head, sizeof(DPK_HEADER), 1, dpk );
}

void DPK_ReverseHeader( DPK_HEADER *head )
{
	CM_ByteSwap32R( &head->block_size );
	CM_ByteSwap32R( &head->entry_num );
	CM_ByteSwap32R( &head->entry_end );
	CM_ByteSwap32R( &head->entry_size );
}

int DPK_CheckHeader( DPK_HEADER *head )
{
	union32 id_be, id_le;
	id_be.u8[0] = 'D'; id_le.u8[0] = 'F';
	id_be.u8[1] = 'I'; id_le.u8[1] = 'R';
	id_be.u8[2] = 'R'; id_le.u8[2] = 'I';
	id_be.u8[3] = 'F'; id_le.u8[3] = 'D';
	
	// check format ID
	if(( head->format_id != id_le.u32 )
	&& ( head->format_id != id_be.u32 ))
	{
		printf( "\nERROR: Invalid Format ID\n" );
		printf( "Expected : 'DIRF' or 'FRID'\n" );
		printf( "Found    : '%.4s'\n", (char *)&head->format_id );
		return NG;
	}
	
	// check attribute
	if(( head->attribute == DPK_ATTR_LE )
	&& ( head->format_id == id_le.u32 )){
		dpkEndianFlag = CM_ENDIAN_LIL;
	}
	else if(( head->attribute == DPK_ATTR_BE )
	/**/ && ( head->format_id == id_be.u32 )){
		dpkEndianFlag = CM_ENDIAN_BIG;
	} else {
		printf( "\nERROR: Invalid Attribute\n" );
		printf( "Expected : 0x%08x or 0x%08x\n", DPK_ATTR_LE, DPK_ATTR_BE );
		printf( "Found    : 0x%08x\n", head->attribute );
		return NG;
	}
	
	// all checks passed
	printf( "Header is OK\n" );
	return OK;
}

/*---------------------------------------------------------------------------*
 * DPK Entry Table
 *---------------------------------------------------------------------------*/
void DPK_LoadEntryTable( DPK_ENTRY *table, DPK_HEADER *head, FILE *dpk )
{
	fseek( dpk, sizeof(DPK_HEADER), SEEK_SET );
	fread( table, sizeof(DPK_ENTRY), head->entry_num, dpk );
}

void DPK_ReverseEntryTable( DPK_ENTRY *table, DPK_HEADER *head )
{
	for( int i=0 ; i < head->entry_num ; i++ ){
		CM_ByteSwap32R( &table[i].offset );
		CM_ByteSwap32R( &table[i].length );
		CM_ByteSwap32R( &table[i].checksum );
	}
}

/*---------------------------------------------------------------------------*
 * DPK File Extract
 *---------------------------------------------------------------------------*/
int DPK_CreateOutputDir( char *dir, char *arg )
{
	// copy filename
	strcpy( dir, arg );
	// remove extension
	*strrchr( dir, '.' ) = 0;
	
	printf( "\nOutput Directory: %s\n", dir );
	
	if( CM_MakeDir( dir ) < 0 ){
		printf( "ERROR: Could not create %s\n", dir );
		return NG;
	}
	return OK;
}

int DPK_ExtractFile(
DPK_ENTRY   *table, /* DPK entry table */
u_int       index,  /* DPK entry index */
FILE        *dpk,   /* DPK file ptr    */
FILE        *out,   /* ouput file ptr  */
char        *name,  /* ouput file name */
char        *dir    /* ouput file dir  */
){
	snprintf( name, MAX_PATH_CHAR, "%s/%.12s", dir, table[index].name );
	
	MakePath( name );
	
	// error check
	if( !( out = fopen( name, "wb" ) ) ){
		printf( "ERROR: Could not create %s\n", name );
		fclose( out );
		return NG;
	}
	
	char *buffer = malloc( table[index].length );
	
	fseek( dpk, table[index].offset, SEEK_SET );
	fread( buffer, table[index].length, 1, dpk );
	fwrite( buffer, 1, table[index].length, out );
	
	// cleanup
	fclose( out );
	free( buffer );
	return OK;
}

/*---------------------------------------------------------------------------*
 * Program Control Flow
 *---------------------------------------------------------------------------*/
#ifndef BUILD_LIBRARY
int main( int argc, char **argv )
{
	FILE *fin, *fout;
	char fout_name[ MAX_PATH_CHAR ] = { 0 };
	
	DPK_HEADER *dpkHeader;
	DPK_ENTRY  *dpkEntryTable;
	
/*---------------------------------------------------------------------------*/
	
	// user error check
	if( argc != 2 ){
		printf( "Wrong number of arguments.\n" );
		printf( "Use: %s example.dpk\n", argv[0] );
		goto cleanup_exit;
	}
	
	// file error check
	if( !(fin = fopen( argv[1], "rb" )) ){
		printf( "ERROR: Could not open %s\n", argv[1] );
		goto cleanup_exit;
	}
	
	// extension check
	char *argv1_ext = strrchr( argv[1], '.' );
	if( !argv1_ext ) goto ext_error;
	
	if(( strcmp( argv1_ext, ".dpk" ) )
	&& ( strcmp( argv1_ext, ".DPK" ) )){
ext_error:
		printf( "ERROR: Filename must end with \".dpk\" or \".DPK\"\n" );
		goto cleanup_fclose;
	}
	
/*---------------------------------------------------------------------------*/
	
	dpkHeader = malloc( sizeof(DPK_HEADER) );
	DPK_LoadHeader( dpkHeader, fin );
	
	// header error check
	if( DPK_CheckHeader( dpkHeader ) < 0 )
		goto cleanup_free;
	
	// make dpkHeader usable on host
	if(( dpkEndianFlag == CM_ENDIAN_BIG ) && ( CM_IsLittleEndian() )
	|| ( dpkEndianFlag == CM_ENDIAN_LIL ) && ( CM_IsBigEndian() ))
		DPK_ReverseHeader( dpkHeader );
	
	printf( "dpkHeader->format_id  : %.4s\n", (char *)&dpkHeader->format_id );
	printf( "dpkHeader->attribute  : %08x\n", dpkHeader->attribute );
	printf( "dpkHeader->block_size : %08x\n", dpkHeader->block_size );
	printf( "dpkHeader->entry_num  : %d\n",   dpkHeader->entry_num );
	printf( "dpkHeader->entry_end  : %08x\n", dpkHeader->entry_end );
	printf( "dpkHeader->entry_size : %08x\n", dpkHeader->entry_size );
	
/*---------------------------------------------------------------------------*/
	
	dpkEntryTable = malloc( dpkHeader->entry_num * sizeof(DPK_ENTRY) );
	DPK_LoadEntryTable( dpkEntryTable, dpkHeader, fin );
	
	// make dpkEntryTable usable on host
	if(( dpkEndianFlag == CM_ENDIAN_BIG ) && ( CM_IsLittleEndian() )
	|| ( dpkEndianFlag == CM_ENDIAN_LIL ) && ( CM_IsBigEndian() ))
		DPK_ReverseEntryTable( dpkEntryTable, dpkHeader );
	
	char *outdir = malloc( strlen(argv[1])+1 ); // +1 for NULL byte
	
	if( DPK_CreateOutputDir( outdir, argv[1] ) < 0 )
		goto cleanup_free;
	
	// table header
	printf( "\n%-12s %-8s %-8s %-8s\n", "Name", "Offset", "Length", "Checksum" );
	printf( "---------------------------------------\n" );
	
	for( u_int i=0 ; i < dpkHeader->entry_num ; i++ ){
		printf( "%-12s %08x %08x %08x\n",
			dpkEntryTable[i].name,
			dpkEntryTable[i].offset,
			dpkEntryTable[i].length,
			dpkEntryTable[i].checksum );
		
		if( DPK_ExtractFile( dpkEntryTable, i, fin, fout, fout_name, outdir ) < 0 )
			goto cleanup_free;
	}
	
/*---------------------------------------------------------------------------*/
	
cleanup_free:
	free( outdir );
	free( dpkEntryTable );
	free( dpkHeader );
cleanup_fclose:
	fclose( fin );
cleanup_exit:
	printf( "\n***** Program Exit *****\n" );
	return 0;
}
#endif /* !BUILD_LIBRARY */

/*---------------------------------------------------------------------------*
 * END OF FILE
 *---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: c; -*- */
/* vim: set noet ts=4 sw=4 ft=c ff=dos fenc=utf-8 : */
