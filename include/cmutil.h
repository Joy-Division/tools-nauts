/*
 *【 LibCM 】by J.Ingram
 * Common Utilities
 */
#ifndef INC_CMUTIL_H
#define INC_CMUTIL_H

#include <stddef.h>  /* for size_t */
#include "cmconf.h"  /* type flags */
#include "cmtypes.h" /* typedefs   */

/*---------------------------------------------------------------------------*
 * Size Macros
 *---------------------------------------------------------------------------*/
#define CM_KBtoBYTE(x)  (size_t)((x) << 10)
#define CM_MBtoBYTE(x)  (size_t)((x) << 20)
#define CM_GBtoBYTE(x)  (size_t)((x) << 30)

/* Will always round down if !( x >= n ) */
#define CM_BYTEtoKB(x)  (size_t)((x) >> 10)
#define CM_BYTEtoMB(x)  (size_t)((x) >> 20)
#define CM_BYTEtoGB(x)  (size_t)((x) >> 30)

/*---------------------------------------------------------------------------*
 * 128-bit Setter Functions
 *---------------------------------------------------------------------------*/
#if defined( HASTYPE_INT128 )

/* Set Int128 with 64-bit (x2) */
static inline void CM_SetInt128w64(
uint128 *dst, // destination
uint64 hi64,  // upper 64b
uint64 lo64   // lower 64b
){
	union128 *tmp = (union128 *)dst;
#ifdef TARGET_BIG_ENDIAN
	tmp->u64[0] = hi64;
	tmp->u64[1] = lo64;
#else
	tmp->u64[1] = hi64;
	tmp->u64[0] = lo64;
#endif
}

/* Set Int128 with 32-bit (x4) */
static inline void CM_SetInt128w32(
uint128 *dst, // destination
uint32 hi32a, // highest 32b
uint32 hi32b, //  higher 32b
uint32 lo32a, //   lower 32b
uint32 lo32b  //  lowest 32b
){
	union128 *tmp = (union128 *)dst;
#ifdef TARGET_BIG_ENDIAN
	tmp->u32[0] = hi32a;
	tmp->u32[1] = hi32b;
	tmp->u32[2] = lo32a;
	tmp->u32[3] = lo32b;
#else
	tmp->u32[3] = hi32a;
	tmp->u32[2] = hi32b;
	tmp->u32[1] = lo32a;
	tmp->u32[0] = lo32b;
#endif
}

/* Set Int128 with 16-bit (x8) */
static inline void CM_SetInt128w16(
uint128 *dst, // destination
uint16 hi16a, // highest 16b of upper 64b
uint16 hi16b, //  higher 16b of upper 64b
uint16 hi16c, //   lower 16b of upper 64b
uint16 hi16d, //  lowest 16b of upper 64b
uint16 lo16a, // highest 16b of lower 64b
uint16 lo16b, //  higher 16b of lower 64b
uint16 lo16c, //   lower 16b of lower 64b
uint16 lo16d  //  lowest 16b of lower 64b
){
	union128 *tmp = (union128 *)dst;
#ifdef TARGET_BIG_ENDIAN
	tmp->u16[0] = hi16a;
	tmp->u16[1] = hi16b;
	tmp->u16[2] = hi16c;
	tmp->u16[3] = hi16d;
	tmp->u16[4] = lo16a;
	tmp->u16[5] = lo16b;
	tmp->u16[6] = lo16c;
	tmp->u16[7] = lo16d;
#else
	tmp->u16[7] = hi16a;
	tmp->u16[6] = hi16b;
	tmp->u16[5] = hi16c;
	tmp->u16[4] = hi16d;
	tmp->u16[3] = lo16a;
	tmp->u16[2] = lo16b;
	tmp->u16[1] = lo16c;
	tmp->u16[0] = lo16d;
#endif
}

/* Set Int128 with 8-bit (x16) */
static inline void CM_SetInt128w8(
uint128 *dst, // destination
uint8 hi08a,  // highest 8b of highest 32b
uint8 hi08b,  //  higher 8b of highest 32b
uint8 hi08c,  //   lower 8b of highest 32b
uint8 hi08d,  //  lowest 8b of highest 32b
uint8 hi08e,  // highest 8b of  higher 32b
uint8 hi08f,  //  higher 8b of  higher 32b
uint8 hi08g,  //   lower 8b of  higher 32b
uint8 hi08h,  //  lowest 8b of  higher 32b
uint8 lo08a,  // highest 8b of   lower 32b
uint8 lo08b,  //  higher 8b of   lower 32b
uint8 lo08c,  //   lower 8b of   lower 32b
uint8 lo08d,  //  lowest 8b of   lower 32b
uint8 lo08e,  // highest 8b of  lowest 32b
uint8 lo08f,  //  higher 8b of  lowest 32b
uint8 lo08g,  //   lower 8b of  lowest 32b
uint8 lo08h   //  lowest 8b of  lowest 32b
){
	union128 *tmp = (union128 *)dst;
#ifdef TARGET_BIG_ENDIAN
	tmp->u8[ 0] = hi08a;
	tmp->u8[ 1] = hi08b;
	tmp->u8[ 2] = hi08c;
	tmp->u8[ 3] = hi08d;
	tmp->u8[ 4] = hi08e;
	tmp->u8[ 5] = hi08f;
	tmp->u8[ 6] = hi08g;
	tmp->u8[ 7] = hi08h;
	tmp->u8[ 8] = lo08a;
	tmp->u8[ 9] = lo08b;
	tmp->u8[10] = lo08c;
	tmp->u8[11] = lo08d;
	tmp->u8[12] = lo08e;
	tmp->u8[13] = lo08f;
	tmp->u8[14] = lo08g;
	tmp->u8[15] = lo08h;
#else
	tmp->u8[15] = hi08a;
	tmp->u8[14] = hi08b;
	tmp->u8[13] = hi08c;
	tmp->u8[12] = hi08d;
	tmp->u8[11] = hi08e;
	tmp->u8[10] = hi08f;
	tmp->u8[ 9] = hi08g;
	tmp->u8[ 8] = hi08h;
	tmp->u8[ 7] = lo08a;
	tmp->u8[ 6] = lo08b;
	tmp->u8[ 5] = lo08c;
	tmp->u8[ 4] = lo08d;
	tmp->u8[ 3] = lo08e;
	tmp->u8[ 2] = lo08f;
	tmp->u8[ 1] = lo08g;
	tmp->u8[ 0] = lo08h;
#endif
}

#endif /* HASTYPE_INT128 */

/*---------------------------------------------------------------------------*
 * File/Directory Utils
 *---------------------------------------------------------------------------*/
#if defined( _WIN32 )
#  include <direct.h>
#  define CM_MakeDir(dirname)  mkdir(dirname)
#elif defined( __unix__ ) || defined( __linux__ )
#  include <sys/stat.h>
#  include <sys/types.h>
#  define CM_MakeDir(dirname)  mkdir(dirname, 0777)
#endif

/*---------------------------------------------------------------------------*/
#endif /* END OF FILE */
/*---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: c; -*- */
/* vim: set noet ts=4 sw=4 ft=c ff=dos fenc=utf-8 : */
