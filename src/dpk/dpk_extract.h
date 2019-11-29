/*
 * POLICENAUTS Toolbox
 * DPK File Extractor
 */
#ifndef INC_DPK_EXTRACT_H
#define INC_DPK_EXTRACT_H

#include <stdio.h>
#include "cmtypes.h"
#include "fmt_data.h"

/*---------------------------------------------------------------------------*
 * DPK Header
 *---------------------------------------------------------------------------*/
extern void DPK_LoadHeader    ( DPK_HEADER *head, FILE *dpk );
extern void DPK_ReverseHeader ( DPK_HEADER *head );
extern int  DPK_CheckHeader   ( DPK_HEADER *head );

/*---------------------------------------------------------------------------*
 * DPK Entry Table
 *---------------------------------------------------------------------------*/
extern void DPK_LoadEntryTable    ( DPK_ENTRY *table, DPK_HEADER *head, FILE *dpk );
extern void DPK_ReverseEntryTable ( DPK_ENTRY *table, DPK_HEADER *head );

/*---------------------------------------------------------------------------*
 * DPK File Extract
 *---------------------------------------------------------------------------*/
extern int DPK_CreateOutputDir( char *dir, char *arg );

extern int DPK_ExtractFile(
DPK_ENTRY   *table, /* DPK entry table */
u_int       index,  /* DPK entry index */
FILE        *dpk,   /* DPK file ptr    */
FILE        *out,   /* ouput file ptr  */
char        *name,  /* ouput file name */
char        *dir    /* ouput file dir  */
);

/*---------------------------------------------------------------------------*/
#endif /* END OF FILE */
/*---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: c; -*- */
/* vim: set noet ts=4 sw=4 ft=c ff=dos fenc=utf-8 : */
