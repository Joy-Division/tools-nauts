/*
 *【CM Library】by J.Ingram
 * ByteSwap Utility Functions
 */
#ifndef INC_CMSWAP_H
#define INC_CMSWAP_H

#include "cmconf.h"
#include "cmtypes.h"

/*---------------------------------------------------------------------------*
 * Public Interface (Cast to Signed/Unsigned)
 *---------------------------------------------------------------------------*/
#define CM_ByteSwapS16(val)   (s16)CM_ByteSwap16(val)
#define CM_ByteSwapU16(val)   (u16)CM_ByteSwap16(val)

#define CM_ByteSwapS32(val)   (s32)CM_ByteSwap32(val)
#define CM_ByteSwapU32(val)   (u32)CM_ByteSwap32(val)

#define CM_ByteSwapS64(val)   (s64)CM_ByteSwap64(val)
#define CM_ByteSwapU64(val)   (u64)CM_ByteSwap64(val)

#if defined( HASTYPE_INT128 )
#define CM_ByteSwapS128(val)  (s128)CM_ByteSwap128(val)
#define CM_ByteSwapU128(val)  (u128)CM_ByteSwap128(val)
#endif /* HASTYPE_INT128 */

/*---------------------------------------------------------------------------*
 * Endianness Conversion for Integer Types
 *---------------------------------------------------------------------------*/
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
	
#if ( CHAINED_BYTESWAP )
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
	
#if ( CHAINED_BYTESWAP )
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
	
#if ( CHAINED_BYTESWAP )
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

/*---------------------------------------------------------------------------*
 * Endianness Conversion for Floating Point Types
 *---------------------------------------------------------------------------*/
static inline float32 CM_ByteSwapF32( float32 val )
{
	union32 in = (union32)val, out;
	
#if ( CHAINED_BYTESWAP )
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
	
#if ( CHAINED_BYTESWAP )
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
	
#if ( CHAINED_BYTESWAP )
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
#endif /* END OF FILE */
/*---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: c; -*- */
/* vim: set noet ts=4 sw=4 ft=c ff=dos fenc=utf-8 : */
