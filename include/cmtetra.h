/*
 *【 LibCM 】ver.20200504
 * Copyright (C) 2019 2020 J.Ingram
 * All Rights Reserved.
 */
#ifndef INCLUDED_CMTETRA_H
#define INCLUDED_CMTETRA_H

#include "cmconf.h"
#include "cmtypes.h"

/*===========================================================================*/
/* Combine 32/16/8-bit Values                                                */
/*===========================================================================*/

#define CM_Set16w8( hi8, lo8 ) \
	( (((u16)hi8 << 8) & 0xFF00u) \
	| (((u16)lo8     ) & 0x00FFu) )

/*---------------------------------------------------------------------------*/

#define CM_Set32w16( hi16, lo16 ) \
	( (((u32)hi16 << 16) & 0xFFFF0000u) \
	| (((u32)lo16      ) & 0x0000FFFFu) )

#define CM_Set32w8( hi8a, hi8b, lo8a, lo8b ) \
	( (((u32)hi8a << 24) & 0xFF000000u) \
	| (((u32)hi8b << 16) & 0x00FF0000u) \
	| (((u32)lo8a <<  8) & 0x0000FF00u) \
	| (((u32)lo8b      ) & 0x000000FFu) )

/*---------------------------------------------------------------------------*/

#define CM_Set64w32( hi32, lo32 ) \
	( (((u64)hi32 << 32) & 0xFFFFFFFF00000000ull) \
	| (((u64)lo32      ) & 0x00000000FFFFFFFFull) )

#define CM_Set64w16( hi16a, hi16b, lo16a, lo16b ) \
	( (((u64)hi16a << 48) & 0xFFFF000000000000ull) \
	| (((u64)hi16b << 32) & 0x0000FFFF00000000ull) \
	| (((u64)lo16a << 16) & 0x00000000FFFF0000ull) \
	| (((u64)lo16b      ) & 0x000000000000FFFFull) )

#define CM_Set64w8( hi8a, hi8b, hi8c, hi8d, lo8a, lo8b, lo8c, lo8d ) \
	( (((u64)hi8a << 56) & 0xFF00000000000000ull) \
	| (((u64)hi8b << 48) & 0x00FF000000000000ull) \
	| (((u64)hi8c << 40) & 0x0000FF0000000000ull) \
	| (((u64)hi8d << 32) & 0x000000FF00000000ull) \
	| (((u64)lo8a << 24) & 0x00000000FF000000ull) \
	| (((u64)lo8b << 16) & 0x0000000000FF0000ull) \
	| (((u64)lo8c <<  8) & 0x000000000000FF00ull) \
	| (((u64)lo8d      ) & 0x00000000000000FFull) )

/* needs 128-bit support */
#if defined(CM_HAVE_INT128)

/*===========================================================================*/
/* Set Int128 with 64/32/16/8-bit Values                                     */
/*===========================================================================*/

static inline void CM_Set128w64(
	u_int128    *dst,   /* destination   */
	u_int64     hi64,   /* upper 64 bits */
	u_int64     lo64    /* lower 64 bits */
){
	cmUnion128 *ptr = (cmUnion128 *)dst;
#if (CM_BYTE_ORDER == CM_BIG_ENDIAN)
	ptr->u64[0] = hi64;
	ptr->u64[1] = lo64;
#elif (CM_BYTE_ORDER == CM_LIL_ENDIAN)
	ptr->u64[1] = hi64;
	ptr->u64[0] = lo64;
#endif
}

/*---------------------------------------------------------------------------*/

static inline void CM_Set128w32(
	u_int128 *dst,
	u_int32 hi32a, u_int32 hi32b,
	u_int32 lo32a, u_int32 lo32b
){
	CM_Set128w64( dst,
		CM_Set64w32( hi32a, hi32b ),
		CM_Set64w32( lo32a, lo32b )
	);
}

/*---------------------------------------------------------------------------*/

static inline void CM_Set128w16(
	u_int128 *dst,
	u_int16 hi16a, u_int16 hi16b,
	u_int16 hi16c, u_int16 hi16d,
	u_int16 lo16a, u_int16 lo16b,
	u_int16 lo16c, u_int16 lo16d
){
	CM_Set128w64( dst,
		CM_Set64w16( hi16a, hi16b, hi16c, hi16d ),
		CM_Set64w16( lo16a, lo16b, lo16c, lo16d )
	);
}

/*---------------------------------------------------------------------------*/

static inline void CM_Set128w8(
	u_int128 *dst,
	u_int8 hi8a, u_int8 hi8b, u_int8 hi8c, u_int8 hi8d,
	u_int8 hi8e, u_int8 hi8f, u_int8 hi8g, u_int8 hi8h,
	u_int8 lo8a, u_int8 lo8b, u_int8 lo8c, u_int8 lo8d,
	u_int8 lo8e, u_int8 lo8f, u_int8 lo8g, u_int8 lo8h
){
	CM_Set128w64( dst,
		CM_Set64w8( hi8a, hi8b, hi8c, hi8d, hi8e, hi8f, hi8g, hi8h ),
		CM_Set64w8( lo8a, lo8b, lo8c, lo8d, lo8e, lo8f, lo8g, lo8h )
	);
}

#endif /* CM_HAVE_INT128 */
#endif /* END OF FILE */
