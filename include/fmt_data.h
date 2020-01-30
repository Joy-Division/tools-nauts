#ifndef INC_FMT_DATA_H
#define INC_FMT_DATA_H

#include "cmtypes.h"

/*---------------------------------------------------------------------------*
 * DPK Format Defines
 *---------------------------------------------------------------------------*/
#define DPK_FORMAT_ID   'DIRF' // Magic Number
#define DPK_BLOCK_SIZE  0x800  // CDROM Sector

/* -------------------------- */
/* Little Endian : 0b11100000 */
/* Big Endian    : 0b10100000 */
/* -------------------------- */
#ifdef CM_TARGET_BE
#define DPK_ATTR_LE  0x000000E0 // swapped for BE target
#define DPK_ATTR_BE  0xA0000000
#else
#define DPK_ATTR_LE  0xE0000000
#define DPK_ATTR_BE  0x000000A0 // swapped for LE target
#endif

#pragma pack(push, 1)
typedef struct tDPK_HEADER {
	u_int32 format_id;  // = DPK_FORMAT_ID
	u_int32 attribute;
	u_int32 block_size; // = DPK_BLOCK_SIZE
	u_int32 entry_num;
	u_int32 entry_end;
	u_int32 entry_size; // sizeof(DPK_ENTRY)
	byte    pad[8];
} DPK_HEADER;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct tDPK_ENTRY {
	char    name[12];
	u_int32 offset;
	u_int32 length;
	u_int32 checksum;
} DPK_ENTRY;
#pragma pack(pop)

/*---------------------------------------------------------------------------*
 * PAC Format Defines
 *---------------------------------------------------------------------------*/

/*
 * PLACEHOLDER
 */

/*---------------------------------------------------------------------------*/
#endif /* END OF FILE */
/*---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: c; -*- */
/* vim: set noet ts=4 sw=4 ft=c ff=dos fenc=utf-8 : */
