#ifndef INC_DPK_EXTRACT_H
#define INC_DPK_EXTRACT_H

#include <stdio.h>

/* DPK Header */
void DPK_LoadHeader( FILE *dpk );
void DPK_ReverseHeader( void );

/* DPK Entry Table */
void DPK_LoadEntry( FILE *dpk, int filenum );
void DPK_ReverseEntry( void );

/* DPK Integrity Check */
bool DPK_CheckID( void );
bool DPK_CheckAttribute( void );

/* DPK File Extract */
bool DPK_CreateOutputDir( char *dir, char *arg );
bool DPK_ExtractFile( FILE *dpk, FILE *out, char *name, char *dir );

#endif /* END OF FILE */
