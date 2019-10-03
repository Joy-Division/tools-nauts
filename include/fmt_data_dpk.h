#ifndef INC_FMT_DATA_DPK_H
#define INC_FMT_DATA_DPK_H

#include "cmtypes.h"

#define DPK_FORMAT_ID   'DIRF'
#define DPK_ATTR_LE     0xE0000000
#define DPK_ATTR_BE     0x000000A0 //! swapped for assumed LE target
#define DPK_BLOCK_SIZE  0x800

#pragma pack(push, 1)
typedef struct {
	uint32 formatID;
	uint32 attribute;
	uint32 block_size;
	uint32 file_count;
	uint32 entry_end;
	uint32 entry_size; // sizeof(DPK_ENTRY)
	char   pad[8];
} DPK_HEADER;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	char   name[12];
	uint32 offset;
	uint32 length;
	uint32 checksum;
} DPK_ENTRY;
#pragma pack(pop)

#endif /* END OF FILE */
