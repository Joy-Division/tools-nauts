/*
 *【 LibCM 】by J.Ingram
 * Endianness Utilities
 */
#ifndef INC_CMSWAP_H
#define INC_CMSWAP_H

#include "cmtypes.h"

/*---------------------------------------------------------------------------*/
/* Public Interface (Cast to Signed/Unsigned)                                */
/*---------------------------------------------------------------------------*/
#define CM_ByteSwapS16(val)   (s16)CM_ByteSwap16((u16)val)
#define CM_ByteSwapU16(val)   (u16)CM_ByteSwap16((u16)val)

#define CM_ByteSwapS32(val)   (s32)CM_ByteSwap32((u32)val)
#define CM_ByteSwapU32(val)   (u32)CM_ByteSwap32((u32)val)

#define CM_ByteSwapS64(val)   (s64)CM_ByteSwap64((u64)val)
#define CM_ByteSwapU64(val)   (u64)CM_ByteSwap64((u64)val)

#ifdef HASTYPE_INT128
#define CM_ByteSwapS128(val)  (s128)CM_ByteSwap128((u128)val)
#define CM_ByteSwapU128(val)  (u128)CM_ByteSwap128((u128)val)
#endif

/*---------------------------------------------------------------------------*/
/* Reverse Endianness for Integer Types                                      */
/*---------------------------------------------------------------------------*/
static inline uint16 CM_ByteSwap16( uint16 val )
{
	union16 in = (union16)val, out;
	
	out.u8[0] = in.u8[1];
	out.u8[1] = in.u8[0];
	
	return out.u16;
}

static inline uint32 CM_ByteSwap32( uint32 val )
{
	union32 in = (union32)val, out;
	
#ifdef CHAINED_BYTESWAP
	out.u16[0] = CM_ByteSwap16( in.u16[1] );
	out.u16[1] = CM_ByteSwap16( in.u16[0] );
#else
	out.u8[0] = in.u8[3];
	out.u8[1] = in.u8[2];
	out.u8[2] = in.u8[1];
	out.u8[3] = in.u8[0];
#endif
	return out.u32;
}

static inline uint64 CM_ByteSwap64( uint64 val )
{
	union64 in = (union64)val, out;
	
#ifdef CHAINED_BYTESWAP
	out.u32[0] = CM_ByteSwap32( in.u32[1] );
	out.u32[1] = CM_ByteSwap32( in.u32[0] );
#else
	out.u8[0] = in.u8[7];
	out.u8[1] = in.u8[6];
	out.u8[2] = in.u8[5];
	out.u8[3] = in.u8[4];
	out.u8[4] = in.u8[3];
	out.u8[5] = in.u8[2];
	out.u8[6] = in.u8[1];
	out.u8[7] = in.u8[0];
#endif
	return out.u64;
}

#if defined( HASTYPE_INT128 )
static inline uint128 CM_ByteSwap128( uint128 val )
{
	union128 in = (union128)val, out;
	
#ifdef CHAINED_BYTESWAP
	out.u64[0] = CM_ByteSwap64( in.u64[1] );
	out.u64[1] = CM_ByteSwap64( in.u64[0] );
#else
	out.u8[ 0] = in.u8[15];
	out.u8[ 1] = in.u8[14];
	out.u8[ 2] = in.u8[13];
	out.u8[ 3] = in.u8[12];
	out.u8[ 4] = in.u8[11];
	out.u8[ 5] = in.u8[10];
	out.u8[ 6] = in.u8[ 9];
	out.u8[ 7] = in.u8[ 8];
	out.u8[ 8] = in.u8[ 7];
	out.u8[ 9] = in.u8[ 6];
	out.u8[10] = in.u8[ 5];
	out.u8[11] = in.u8[ 4];
	out.u8[12] = in.u8[ 3];
	out.u8[13] = in.u8[ 2];
	out.u8[14] = in.u8[ 1];
	out.u8[15] = in.u8[ 0];
#endif
	return out.u128;
}
#endif /* HASTYPE_INT128 */

/*---------------------------------------------------------------------------*/
/* Reverse Endianness for Floating Point Types                               */
/*---------------------------------------------------------------------------*/
static inline float32 CM_ByteSwapF32( float32 val )
{
	union32 in = (union32)val, out;
	
#ifdef CHAINED_BYTESWAP
	out.u16[0] = CM_ByteSwap16( in.u16[1] );
	out.u16[1] = CM_ByteSwap16( in.u16[0] );
#else
	out.u8[0] = in.u8[3];
	out.u8[1] = in.u8[2];
	out.u8[2] = in.u8[1];
	out.u8[3] = in.u8[0];
#endif
	return out.f32;
}

static inline float64 CM_ByteSwapF64( float64 val )
{
	union64 in = (union64)val, out;
	
#ifdef CHAINED_BYTESWAP
	out.u32[0] = CM_ByteSwap32( in.u32[1] );
	out.u32[1] = CM_ByteSwap32( in.u32[0] );
#else
	out.u8[0] = in.u8[7];
	out.u8[1] = in.u8[6];
	out.u8[2] = in.u8[5];
	out.u8[3] = in.u8[4];
	out.u8[4] = in.u8[3];
	out.u8[5] = in.u8[2];
	out.u8[6] = in.u8[1];
	out.u8[7] = in.u8[0];
#endif
	return out.f64;
}

#if defined( HASTYPE_FLOAT128 )
static inline float128 CM_ByteSwapF128( float128 val )
{
	union128 in = (union128)val, out;
	
#ifdef CHAINED_BYTESWAP
	out.u64[0] = CM_ByteSwap64( in.u64[1] );
	out.u64[1] = CM_ByteSwap64( in.u64[0] );
#else
	out.u8[ 0] = in.u8[15];
	out.u8[ 1] = in.u8[14];
	out.u8[ 2] = in.u8[13];
	out.u8[ 3] = in.u8[12];
	out.u8[ 4] = in.u8[11];
	out.u8[ 5] = in.u8[10];
	out.u8[ 6] = in.u8[ 9];
	out.u8[ 7] = in.u8[ 8];
	out.u8[ 8] = in.u8[ 7];
	out.u8[ 9] = in.u8[ 6];
	out.u8[10] = in.u8[ 5];
	out.u8[11] = in.u8[ 4];
	out.u8[12] = in.u8[ 3];
	out.u8[13] = in.u8[ 2];
	out.u8[14] = in.u8[ 1];
	out.u8[15] = in.u8[ 0];
#endif
	return out.f128;
}
#endif /* HASTYPE_FLOAT128 */

/*---------------------------------------------------------------------------*/
/* Reverse Endianness (Pass by Reference)                                    */
/*---------------------------------------------------------------------------*/
static inline void CM_ByteSwap16R( void *val )
{
	union16 *in = (union16 *)val;
	union16 tmp; tmp.u16 = in->u16;
	
	in->u8[0] = tmp.u8[1];
	in->u8[1] = tmp.u8[0];
}

static inline void CM_ByteSwap32R( void *val )
{
	union32 *in = (union32 *)val;
	union32 tmp; tmp.u32 = in->u32;
	
	in->u8[0] = tmp.u8[3];
	in->u8[1] = tmp.u8[2];
	in->u8[2] = tmp.u8[1];
	in->u8[3] = tmp.u8[0];
}

static inline void CM_ByteSwap64R( void *val )
{
	union64 *in = (union64 *)val;
	union64 tmp; tmp.u64 = in->u64;
	
	in->u8[0] = tmp.u8[7];
	in->u8[1] = tmp.u8[6];
	in->u8[2] = tmp.u8[5];
	in->u8[3] = tmp.u8[4];
	in->u8[4] = tmp.u8[3];
	in->u8[5] = tmp.u8[2];
	in->u8[6] = tmp.u8[1];
	in->u8[7] = tmp.u8[0];
}

#if defined( HASTYPE_INT128 )
static inline void CM_ByteSwap128R( void *val )
{
	union128 *in = (union128 *)val;
	union128 tmp; tmp.u128 = in->u128;
	
	in->u8[ 0] = tmp.u8[15];
	in->u8[ 1] = tmp.u8[14];
	in->u8[ 2] = tmp.u8[13];
	in->u8[ 3] = tmp.u8[12];
	in->u8[ 4] = tmp.u8[11];
	in->u8[ 5] = tmp.u8[10];
	in->u8[ 6] = tmp.u8[ 9];
	in->u8[ 7] = tmp.u8[ 8];
	in->u8[ 8] = tmp.u8[ 7];
	in->u8[ 9] = tmp.u8[ 6];
	in->u8[10] = tmp.u8[ 5];
	in->u8[11] = tmp.u8[ 4];
	in->u8[12] = tmp.u8[ 3];
	in->u8[13] = tmp.u8[ 2];
	in->u8[14] = tmp.u8[ 1];
	in->u8[15] = tmp.u8[ 0];
}
#endif /* HASTYPE_INT128 */

/*---------------------------------------------------------------------------*/
/* Get Native Endianness                                                     */
/*---------------------------------------------------------------------------*/
#define CM_ENDIAN_LIL (0)
#define CM_ENDIAN_BIG (1)

static inline bool8 CM_IsBigEndian( void )
{
	u_int32 test_val = 0x01FFFF00;
	union32 *test_ptr = (union32 *)&test_val;
	
	return test_ptr->u8[0];
}

static inline bool8 CM_IsLittleEndian( void )
{
	u_int32 test_val = 0x00FFFF01;
	union32 *test_ptr = (union32 *)&test_val;
	
	return test_ptr->u8[0];
}

/*---------------------------------------------------------------------------*/
#endif /* END OF FILE */
/*---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: c; -*- */
/* vim: set noet ts=4 sw=4 ft=c ff=unix fenc=utf-8 : */
