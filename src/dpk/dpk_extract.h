/*
 * POLICENAUTS Toolbox
 * DPK File Extractor
 *
 * Copyright (C) 2017 2020 J.Ingram
 * Special thanks to Missingno_force
 */
#ifndef INCLUDED_DPK_EXTRACT_H
#define INCLUDED_DPK_EXTRACT_H

#include <stdio.h>
#include "cmtypes.h"
#include "fmt_data.h"

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*
 * DPK FILE Context
 *---------------------------------------------------------------------------*/
typedef struct {
	DPK_HEADER *header;         // pointer to DPK_HEADER buffer
	DPK_ENTRY  *entry_table;    // pointer to DPK_ENTRY array buffer
	u_int32     endian_flag;    // DPK file endianness
} dpkWork;

/*---------------------------------------------------------------------------*
 * DPK Header
 *---------------------------------------------------------------------------*/
void DPK_HeaderLoad    ( dpkWork *work, FILE *dpk );
void DPK_HeaderReverse ( dpkWork *work );
int  DPK_HeaderCheck   ( dpkWork *work );

/*---------------------------------------------------------------------------*
 * DPK Entry Table
 *---------------------------------------------------------------------------*/
void DPK_EntryTableLoad    ( dpkWork *work, FILE *dpk );
void DPK_EntryTableReverse ( dpkWork *work );

/*---------------------------------------------------------------------------*
 * DPK File Extract
 *---------------------------------------------------------------------------*/
int DPK_CreateOutputDir( char *dir, char *arg );

int DPK_ExtractFile(
	dpkWork *work,  /* DPK work struct */
	u_int   index,  /* DPK entry index */
	FILE    *dpk,   /* DPK file ptr    */
	FILE    *out,   /* ouput file ptr  */
	char    *name,  /* ouput file name */
	char    *dir    /* ouput file dir  */
);

#ifdef __cplusplus
}
#endif

#endif /* END OF FILE */
