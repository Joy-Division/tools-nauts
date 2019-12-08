#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cmutil.h"

/*
 * Generously donated by Missingno_force
 */
void MakePath( char *path )
{
//	printf("making directory %s\n", path);
	
	FILE *tmp = NULL;
	
	if( tmp = fopen( path, "wb" ) ){
		remove( path );
		fclose( tmp );
		return;
	}
	
	char bakpath[2048] = { 0 };
	char curpath[2048] = { 0 };
	char *token = NULL;
	
	strcpy( bakpath, path );
	token = strtok( bakpath, "/" );
	strcpy( curpath, token );
	
	while( token ){
		CM_MakeDir( curpath );
//		printf("creating directory %s\n", curpath );
		strcat( curpath, "/" );
		token = strtok( NULL, "/" );
		strcat( curpath, token );
		if ( tmp = fopen( path, "wb" ) ) break;
	}
	
	fclose( tmp );
	remove( path );
	fflush( stdout );
	return;
}

/*---------------------------------------------------------------------------*/
// END OF FILE
/*---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: c; -*- */
/* vim: set noet ts=4 sw=4 ft=c ff=dos fenc=utf-8 : */
