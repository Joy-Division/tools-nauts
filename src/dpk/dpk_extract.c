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

#ifndef MAX_PATH
#define MAX_PATH 260
#endif

#include "dpk_extract.h"
#include "fmt_data.h"

/*---------------------------------------------------------------------------*
 * DPK Header
 *---------------------------------------------------------------------------*/
void DPK_HeaderLoad( dpkWork *work, FILE *dpk )
{
	fseek( dpk, 0, SEEK_SET );
	fread( work->dpkHeader, sizeof(DPK_HEADER), 1, dpk );
}

void DPK_HeaderReverse( dpkWork *work )
{
	CM_ByteSwapR32( &work->dpkHeader->block_size );
	CM_ByteSwapR32( &work->dpkHeader->entry_num );
	CM_ByteSwapR32( &work->dpkHeader->entry_end );
	CM_ByteSwapR32( &work->dpkHeader->entry_size );
}

int DPK_HeaderCheck( dpkWork *work )
{
	union32 id_be = { .u8 = {'D','I','R','F'} };
	union32 id_le = { .u8 = {'F','R','I','D'} };
	
	// check format ID
	if(( work->dpkHeader->format_id != id_le.u32 )
	&& ( work->dpkHeader->format_id != id_be.u32 ))
	{
		printf( "\nERROR: Invalid Format ID\n" );
		printf( "Expected : 'DIRF' or 'FRID'\n" );
		printf( "Found    : '%.4s'\n", (char *)&work->dpkHeader->format_id );
		return NG;
	}
	
	// check attribute
	if(( work->dpkHeader->attribute == DPK_ATTR_LE )
	&& ( work->dpkHeader->format_id == id_le.u32 )){
		work->dpkEndianFlag = CM_ENDIAN_ID_LE;
	}
	else if(( work->dpkHeader->attribute == DPK_ATTR_BE )
	/**/ && ( work->dpkHeader->format_id == id_be.u32 )){
		work->dpkEndianFlag = CM_ENDIAN_ID_BE;
	} else {
		printf( "\nERROR: Invalid Attribute\n" );
		printf( "Expected : 0x%08x or 0x%08x\n", DPK_ATTR_LE, DPK_ATTR_BE );
		printf( "Found    : 0x%08x\n", work->dpkHeader->attribute );
		return NG;
	}
	
	// all checks passed
	printf( "Header is OK\n" );
	return OK;
}

/*---------------------------------------------------------------------------*
 * DPK Entry Table
 *---------------------------------------------------------------------------*/
void DPK_EntryTableLoad( dpkWork *work, FILE *dpk )
{
	fseek( dpk, sizeof(DPK_HEADER), SEEK_SET );
	fread( work->dpkEntryTable, sizeof(DPK_ENTRY), work->dpkHeader->entry_num, dpk );
}

void DPK_EntryTableReverse( dpkWork *work )
{
	for( int i=0 ; i < work->dpkHeader->entry_num ; i++ ){
		CM_ByteSwapR32( &work->dpkEntryTable[i].offset );
		CM_ByteSwapR32( &work->dpkEntryTable[i].length );
		CM_ByteSwapR32( &work->dpkEntryTable[i].checksum );
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
dpkWork *work,  /* DPK work struct */
u_int   index,  /* DPK entry index */
FILE    *dpk,   /* DPK file ptr    */
FILE    *out,   /* ouput file ptr  */
char    *name,  /* ouput file name */
char    *dir    /* ouput file dir  */
){
	snprintf( name, MAX_PATH, "%s/%.12s", dir, work->dpkEntryTable[index].name );
	
	MakePath( name );
	
	// error check
	if( !( out = fopen( name, "wb" ) ) ){
		printf( "ERROR: Could not create %s\n", name );
		fclose( out );
		return NG;
	}
	
	char *buffer = malloc( work->dpkEntryTable[index].length );
	
	fseek( dpk, work->dpkEntryTable[index].offset, SEEK_SET );
	fread( buffer, work->dpkEntryTable[index].length, 1, dpk );
	fwrite( buffer, 1, work->dpkEntryTable[index].length, out );
	
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
	char fout_name[ MAX_PATH ] = { 0 };
	
	dpkWork work = {
		.dpkHeader     = NULL,
		.dpkEntryTable = NULL,
		.dpkEndianFlag = -1
	};
	
/*///////////////////////////////////////////////////////////////////////////*/
	
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
	
/*///////////////////////////////////////////////////////////////////////////*/
	
	work.dpkHeader = malloc( sizeof(DPK_HEADER) );
	DPK_HeaderLoad( &work, fin );
	
	// header error check
	if( DPK_HeaderCheck( &work ) < 0 )
		goto cleanup_free;
	
	// make dpkHeader usable on host
	if(( work.dpkEndianFlag == CM_ENDIAN_ID_BE ) && ( CM_IsLittleEndian() )
	|| ( work.dpkEndianFlag == CM_ENDIAN_ID_LE ) && ( CM_IsBigEndian() ))
		DPK_HeaderReverse( &work );
	
	printf( "work.dpkHeader->format_id  : %.4s\n", (char *)&work.dpkHeader->format_id );
	printf( "work.dpkHeader->attribute  : %08x\n", work.dpkHeader->attribute );
	printf( "work.dpkHeader->block_size : %08x\n", work.dpkHeader->block_size );
	printf( "work.dpkHeader->entry_num  : %d\n",   work.dpkHeader->entry_num );
	printf( "work.dpkHeader->entry_end  : %08x\n", work.dpkHeader->entry_end );
	printf( "work.dpkHeader->entry_size : %08x\n", work.dpkHeader->entry_size );
	
/*///////////////////////////////////////////////////////////////////////////*/
	
	work.dpkEntryTable = malloc( work.dpkHeader->entry_num * sizeof(DPK_ENTRY) );
	DPK_EntryTableLoad( &work, fin );
	
	// make dpkEntryTable usable on host
	if(( work.dpkEndianFlag == CM_ENDIAN_ID_BE ) && ( CM_IsLittleEndian() )
	|| ( work.dpkEndianFlag == CM_ENDIAN_ID_LE ) && ( CM_IsBigEndian() ))
		DPK_EntryTableReverse( &work );
	
	char *outdir = malloc( strlen(argv[1])+1 ); // +1 for NULL byte
	
	if( DPK_CreateOutputDir( outdir, argv[1] ) < 0 )
		goto cleanup_free;
	
	// table header
	printf( "\n%-12s %-8s %-8s %-8s\n", "Name", "Offset", "Length", "Checksum" );
	printf( "---------------------------------------\n" );
	
	for( u_int i=0 ; i < work.dpkHeader->entry_num ; i++ )
	{
		printf( "%-12s %08x %08x %08x\n",
			work.dpkEntryTable[i].name,
			work.dpkEntryTable[i].offset,
			work.dpkEntryTable[i].length,
			work.dpkEntryTable[i].checksum );
		
		if( DPK_ExtractFile( &work, i, fin, fout, fout_name, outdir ) < 0 )
			goto cleanup_free;
	}
	
/*///////////////////////////////////////////////////////////////////////////*/
	
cleanup_free:
	free( outdir );
	free( work.dpkEntryTable );
	free( work.dpkHeader );
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
