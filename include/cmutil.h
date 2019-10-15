/*
 *【CM Library】by J.Ingram
 * Common Utilities
 */
#ifndef INC_CMUTIL_H
#define INC_CMUTIL_H

#include <stddef.h>  /* for size_t */
#include "cmconf.h"  /* type flags */
#include "cmtypes.h" /* typedefs */

/*---------------------------------------------------------------------------*
 * Size Macros
 *---------------------------------------------------------------------------*/
#define CM_KBtoBYTE(x)  (size_t)((x) << 10)
#define CM_MBtoBYTE(x)  (size_t)((x) << 20)
#define CM_GBtoBYTE(x)  (size_t)((x) << 30)

#define CM_BYTEtoKB(x)  (size_t)((x) >> 10)
#define CM_BYTEtoMB(x)  (size_t)((x) >> 20)
#define CM_BYTEtoGB(x)  (size_t)((x) >> 30)

/*---------------------------------------------------------------------------*
 * 128-bit Set Functions
 *---------------------------------------------------------------------------*/
#if defined( HASTYPE_INT128 )

/* Set Int128 with 16-bit (x8) */
static inline void CM_SetInt128_16(
	uint128 *p128,
	uint16 hi16a, uint16 hi16b, uint16 hi16c, uint16 hi16d,
	uint16 lo16a, uint16 lo16b, uint16 lo16c, uint16 lo16d )
{
	union128 *tmp = (union128 *)p128;
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

/* Set Int128 with 32-bit (x4) */
static inline void CM_SetInt128_32(
	uint128 *p128,
	uint32 hi32a, uint32 hi32b,
	uint32 lo32a, uint32 lo32b )
{
	union128 *tmp = (union128 *)p128;
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

/* Set Int128 with 64-bit (x2) */
static inline void CM_SetInt128_64(
	uint128 *p128, uint64 hi64, uint64 lo64 )
{
	union128 *tmp = (union128 *)p128;
#ifdef TARGET_BIG_ENDIAN
	tmp->u64[0] = hi64;
	tmp->u64[1] = lo64;
#else
	tmp->u64[1] = hi64;
	tmp->u64[0] = lo64;
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
