/*
 *【 LibCM 】ver.20200314
 * Copyright (C) 2019 2020 J.Ingram
 * All rights reserved.
 */
/* cmtetra.h
 * Mode TI/TF (128-bit) Utilities
 */
#ifndef INCLUDED_CMTETRA_H
#define INCLUDED_CMTETRA_H

/* needs 128-bit support */
#if defined(CM_HAVE_INT128)

#include "cmconf.h"
#include "cmtypes.h"

/*---------------------------------------------------------------------------*/
/* 128-bit Setter Functions                                                  */
/*---------------------------------------------------------------------------*/

/*---< Set Int128 with 64-bit (x2) >---*/

static inline void CM_Set128w64(
	u_int128 *dst, /* destination */
	u_int64 hi64,  /* upper 64b   */
	u_int64 lo64   /* lower 64b   */
){
	union128 *ptr = (union128 *)dst;
#if (CM_BYTE_ORDER == CM_BIG_ENDIAN)
	ptr->u64[0] = hi64;
	ptr->u64[1] = lo64;
#elif (CM_BYTE_ORDER == CM_LIL_ENDIAN)
	ptr->u64[1] = hi64;
	ptr->u64[0] = lo64;
#endif
}

/*---< Set Int128 with 32-bit (x4) >---*/

static inline void CM_Set128w32(
	u_int128 *dst, /* destination */
	u_int32 hi32a, /* highest 32b */
	u_int32 hi32b, /*  higher 32b */
	u_int32 lo32a, /*   lower 32b */
	u_int32 lo32b  /*  lowest 32b */
){
	union128 *ptr = (union128 *)dst;
#if (CM_BYTE_ORDER == CM_BIG_ENDIAN)
	ptr->u32[0] = hi32a; ptr->u32[1] = hi32b;
	ptr->u32[2] = lo32a; ptr->u32[3] = lo32b;
#elif (CM_BYTE_ORDER == CM_LIL_ENDIAN)
	ptr->u32[3] = hi32a; ptr->u32[2] = hi32b;
	ptr->u32[1] = lo32a; ptr->u32[0] = lo32b;
#endif
}

/*---< Set Int128 with 16-bit (x8) >---*/

static inline void CM_Set128w16(
	u_int128 *dst, /* destination */
	u_int16 hi16a, u_int16 hi16b, /* highest 32b */
	u_int16 hi16c, u_int16 hi16d, /*  higher 32b */
	u_int16 lo16a, u_int16 lo16b, /*   lower 32b */
	u_int16 lo16c, u_int16 lo16d  /*  lowest 32b */
){
	union128 *ptr = (union128 *)dst;
#if (CM_BYTE_ORDER == CM_BIG_ENDIAN)
	ptr->u16[0] = hi16a; ptr->u16[1] = hi16b;
	ptr->u16[2] = hi16c; ptr->u16[3] = hi16d;
	ptr->u16[4] = lo16a; ptr->u16[5] = lo16b;
	ptr->u16[6] = lo16c; ptr->u16[7] = lo16d;
#elif (CM_BYTE_ORDER == CM_LIL_ENDIAN)
	ptr->u16[7] = hi16a; ptr->u16[6] = hi16b;
	ptr->u16[5] = hi16c; ptr->u16[4] = hi16d;
	ptr->u16[3] = lo16a; ptr->u16[2] = lo16b;
	ptr->u16[1] = lo16c; ptr->u16[0] = lo16d;
#endif
}

/*---< Set Int128 with 8-bit (x16) >---*/

static inline void CM_Set128w8(
	u_int128 *dst, /* destination */
	u_int8 hi08a, u_int8 hi08b, /* highest 16b of upper 64b */
	u_int8 hi08c, u_int8 hi08d, /*  higher 16b of upper 64b */
	u_int8 hi08e, u_int8 hi08f, /*   lower 16b of upper 64b */
	u_int8 hi08g, u_int8 hi08h, /*  lowest 16b of upper 64b */
	u_int8 lo08a, u_int8 lo08b, /* highest 16b of lower 64b */
	u_int8 lo08c, u_int8 lo08d, /*  higher 16b of lower 64b */
	u_int8 lo08e, u_int8 lo08f, /*   lower 16b of lower 64b */
	u_int8 lo08g, u_int8 lo08h  /*  lowest 16b of lower 64b */
){
	union128 *ptr = (union128 *)dst;
#if (CM_BYTE_ORDER == CM_BIG_ENDIAN)
	ptr->u8[ 0] = hi08a; ptr->u8[ 1] = hi08b;
	ptr->u8[ 2] = hi08c; ptr->u8[ 3] = hi08d;
	ptr->u8[ 4] = hi08e; ptr->u8[ 5] = hi08f;
	ptr->u8[ 6] = hi08g; ptr->u8[ 7] = hi08h;
	ptr->u8[ 8] = lo08a; ptr->u8[ 9] = lo08b;
	ptr->u8[10] = lo08c; ptr->u8[11] = lo08d;
	ptr->u8[12] = lo08e; ptr->u8[13] = lo08f;
	ptr->u8[14] = lo08g; ptr->u8[15] = lo08h;
#elif (CM_BYTE_ORDER == CM_LIL_ENDIAN)
	ptr->u8[15] = hi08a; ptr->u8[14] = hi08b;
	ptr->u8[13] = hi08c; ptr->u8[12] = hi08d;
	ptr->u8[11] = hi08e; ptr->u8[10] = hi08f;
	ptr->u8[ 9] = hi08g; ptr->u8[ 8] = hi08h;
	ptr->u8[ 7] = lo08a; ptr->u8[ 6] = lo08b;
	ptr->u8[ 5] = lo08c; ptr->u8[ 4] = lo08d;
	ptr->u8[ 3] = lo08e; ptr->u8[ 2] = lo08f;
	ptr->u8[ 1] = lo08g; ptr->u8[ 0] = lo08h;
#endif
}

#endif /* CM_HAVE_INT128 */
#endif /* END OF FILE */
