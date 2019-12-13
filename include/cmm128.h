/*
 *【 LibCM 】by J.Ingram
 * 128-bit Mode Utilities
 */
#ifndef INC_CMM128_H
#define INC_CMM128_H

#include "cmtypes.h"

#if defined( HASTYPE_INT128 )

/*---------------------------------------------------------------------------*/
/* 128-bit Setter Functions                                                  */
/*---------------------------------------------------------------------------*/

/* Set Int128 with 64-bit (x2) */
static inline void CM_Set128w64(
uint128 *dst, /* destination */
uint64 hi64,  /* upper 64b   */
uint64 lo64   /* lower 64b   */
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
static inline void CM_Set128w32(
uint128 *dst, /* destination */
uint32 hi32a, /* highest 32b */
uint32 hi32b, /*  higher 32b */
uint32 lo32a, /*   lower 32b */
uint32 lo32b  /*  lowest 32b */
){
	union128 *tmp = (union128 *)dst;
#ifdef TARGET_BIG_ENDIAN
	tmp->u32[0] = hi32a; tmp->u32[1] = hi32b;
	tmp->u32[2] = lo32a; tmp->u32[3] = lo32b;
#else
	tmp->u32[3] = hi32a; tmp->u32[2] = hi32b;
	tmp->u32[1] = lo32a; tmp->u32[0] = lo32b;
#endif
}

/* Set Int128 with 16-bit (x8) */
static inline void CM_Set128w16(
uint128 *dst, /* destination */
uint16 hi16a, uint16 hi16b, /* highest 32b */
uint16 hi16c, uint16 hi16d, /*  higher 32b */
uint16 lo16a, uint16 lo16b, /*   lower 32b */
uint16 lo16c, uint16 lo16d  /*  lowest 32b */
){
	union128 *tmp = (union128 *)dst;
#ifdef TARGET_BIG_ENDIAN
	tmp->u16[0] = hi16a; tmp->u16[1] = hi16b;
	tmp->u16[2] = hi16c; tmp->u16[3] = hi16d;
	tmp->u16[4] = lo16a; tmp->u16[5] = lo16b;
	tmp->u16[6] = lo16c; tmp->u16[7] = lo16d;
#else
	tmp->u16[7] = hi16a; tmp->u16[6] = hi16b;
	tmp->u16[5] = hi16c; tmp->u16[4] = hi16d;
	tmp->u16[3] = lo16a; tmp->u16[2] = lo16b;
	tmp->u16[1] = lo16c; tmp->u16[0] = lo16d;
#endif
}

/* Set Int128 with 8-bit (x16) */
static inline void CM_Set128w8(
uint128 *dst, /* destination */
uint8 hi08a, uint8 hi08b, /* highest 16b of upper 64b */
uint8 hi08c, uint8 hi08d, /*  higher 16b of upper 64b */
uint8 hi08e, uint8 hi08f, /*   lower 16b of upper 64b */
uint8 hi08g, uint8 hi08h, /*  lowest 16b of upper 64b */
uint8 lo08a, uint8 lo08b, /* highest 16b of lower 64b */
uint8 lo08c, uint8 lo08d, /*  higher 16b of lower 64b */
uint8 lo08e, uint8 lo08f, /*   lower 16b of lower 64b */
uint8 lo08g, uint8 lo08h  /*  lowest 16b of lower 64b */
){
	union128 *tmp = (union128 *)dst;
#ifdef TARGET_BIG_ENDIAN
	tmp->u8[ 0] = hi08a; tmp->u8[ 1] = hi08b;
	tmp->u8[ 2] = hi08c; tmp->u8[ 3] = hi08d;
	tmp->u8[ 4] = hi08e; tmp->u8[ 5] = hi08f;
	tmp->u8[ 6] = hi08g; tmp->u8[ 7] = hi08h;
	tmp->u8[ 8] = lo08a; tmp->u8[ 9] = lo08b;
	tmp->u8[10] = lo08c; tmp->u8[11] = lo08d;
	tmp->u8[12] = lo08e; tmp->u8[13] = lo08f;
	tmp->u8[14] = lo08g; tmp->u8[15] = lo08h;
#else
	tmp->u8[15] = hi08a; tmp->u8[14] = hi08b;
	tmp->u8[13] = hi08c; tmp->u8[12] = hi08d;
	tmp->u8[11] = hi08e; tmp->u8[10] = hi08f;
	tmp->u8[ 9] = hi08g; tmp->u8[ 8] = hi08h;
	tmp->u8[ 7] = lo08a; tmp->u8[ 6] = lo08b;
	tmp->u8[ 5] = lo08c; tmp->u8[ 4] = lo08d;
	tmp->u8[ 3] = lo08e; tmp->u8[ 2] = lo08f;
	tmp->u8[ 1] = lo08g; tmp->u8[ 0] = lo08h;
#endif
}

#endif /* HASTYPE_INT128 */
/*---------------------------------------------------------------------------*/
#endif /* END OF FILE */
/*---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: c; -*- */
/* vim: set noet ts=4 sw=4 ft=c ff=unix fenc=utf-8 : */
