#ifndef INC_FMT_DATA_H
#define INC_FMT_DATA_H

#include "cmtypes.h"

/*---------------------------------------------------------------------------*
 * DPK Format Defines
 *---------------------------------------------------------------------------*/
#define DPK_FORMAT_ID   'DIRF'
#define DPK_BLOCK_SIZE  0x800

// --------------------------
// Little Endian : 0b11100000
// Big Endian    : 0b10100000
// --------------------------
#ifdef TARGET_BIG_ENDIAN
#define DPK_ATTR_LE  0x000000E0 // swapped for target endianness
#define DPK_ATTR_BE  0xA0000000
#else
#define DPK_ATTR_LE  0xE0000000
#define DPK_ATTR_BE  0x000000A0 // swapped for target endianness
#endif

#pragma pack(push, 1)
typedef struct tDPK_HEADER {
	u_int32 format_id;  // 'DIRF'
	u_int32 attribute;
	u_int32 block_size;
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

#endif /* END OF FILE */
