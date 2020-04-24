/*
 *【 LibCM 】ver.20200423
 * Copyright (C) 2019 2020 J.Ingram
 * All Rights Reserved.
 */
/* cmswap.h
 * Endianness Utilities
 */
#ifndef INCLUDED_CMSWAP_H
#define INCLUDED_CMSWAP_H

#include "cmconf.h"
#include "cmtypes.h"

/*---------------------------------------------------------------------------*/
/* ByteSwap for Integer Types                                                */
/*---------------------------------------------------------------------------*/

#define CM_SwapS16( val ) \
	(s16)CM_SwapU16( (u16)val )

static inline u_int16 CM_SwapU16( u_int16 val )
{
	return ( ((val >> 8) & 0x00FF) | ((val << 8) & 0xFF00) );
}

/*---------------------------------------------------------------------------*/

#define CM_SwapS32( val ) \
	(s32)CM_SwapU32( (u32)val )

static inline u_int32 CM_SwapU32( u_int32 val )
{
	return
		( ((val >> 24) & 0x000000FF)
		| ((val >>  8) & 0x0000FF00)
		| ((val <<  8) & 0x00FF0000)
		| ((val << 24) & 0xFF000000) );
}

/*---------------------------------------------------------------------------*/

#define CM_SwapS64( val ) \
	(s64)CM_SwapU64( (u64)val )

static inline u_int64 CM_SwapU64( u_int64 val )
{
	return
		( ((val >> 56) & 0x00000000000000FFLL)
		| ((val >> 40) & 0x000000000000FF00LL)
		| ((val >> 24) & 0x0000000000FF0000LL)
		| ((val >>  8) & 0x00000000FF000000LL)
		| ((val <<  8) & 0x000000FF00000000LL)
		| ((val << 24) & 0x0000FF0000000000LL)
		| ((val << 40) & 0x00FF000000000000LL)
		| ((val << 56) & 0xFF00000000000000LL) );
}

/*---------------------------------------------------------------------------*/

#ifdef CM_HAVE_INT128

#define CM_SwapS128( val ) \
	(s128)CM_SwapU128( (u128)val )

static inline u_int128 CM_SwapU128( u_int128 val )
{
	cmUnion128 in = {.u128 = val}, out;

	out.u64[0] = CM_SwapU64( in.u64[1] );
	out.u64[1] = CM_SwapU64( in.u64[0] );

	return out.u128;
}
#endif /* CM_HAVE_INT128 */

/*---------------------------------------------------------------------------*/
/* ByteSwap for Floating Point Types w/ Fixed-Width                          */
/*---------------------------------------------------------------------------*/

#define CM_SwapFloat( val ) \
	CM_SwapF32( (f32)val )

static inline float32 CM_SwapF32( float32 val )
{
	cmUnion32 in = {.f32 = val}, out;

	out.u16[0] = CM_SwapU16( in.u16[1] );
	out.u16[1] = CM_SwapU16( in.u16[0] );

	return out.f32;
}

/*---------------------------------------------------------------------------*/

#define CM_SwapDouble( val ) \
	CM_SwapF64( (f64)val )

static inline float64 CM_SwapF64( float64 val )
{
	cmUnion64 in = {.f64 = val}, out;

	out.u32[0] = CM_SwapU32( in.u32[1] );
	out.u32[1] = CM_SwapU32( in.u32[0] );

	return out.f64;
}

/*---------------------------------------------------------------------------*/

#ifdef CM_HAVE_FLOAT128
static inline float128 CM_SwapF128( float128 val )
{
	cmUnion128 in = {.f128 = val}, out;

	out.u64[0] = CM_SwapU64( in.u64[1] );
	out.u64[1] = CM_SwapU64( in.u64[0] );

	return out.f128;
}
#endif /* CM_HAVE_FLOAT128 */

/*---------------------------------------------------------------------------*/
/* ByteSwap for Floating Point Types w/ Target-Dependent Width               */
/*---------------------------------------------------------------------------*/

static inline long double CM_SwapLongDouble( long double val )
{
	long double tmp;
	u_byte *in = (u_byte *)&val;
	u_byte *out = (u_byte *)&tmp;

	const int SIZE = sizeof(long double);

	for( int i=0, j=(SIZE-1); i < SIZE; i++, j-- )
	{
		out[i] = in[j];
	}
	return tmp;
}

/*---------------------------------------------------------------------------*/
/* ByteSwap (Pass by Reference)                                              */
/*---------------------------------------------------------------------------*/

static inline void CM_SwapR16( void *ref )
{
	*(u_int16 *)ref = CM_SwapU16( *(u_int16 *)ref );
}

/*---------------------------------------------------------------------------*/

static inline void CM_SwapR32( void *ref )
{
	*(u_int32 *)ref = CM_SwapU32( *(u_int32 *)ref );
}

/*---------------------------------------------------------------------------*/

static inline void CM_SwapR64( void *ref )
{
	*(u_int64 *)ref = CM_SwapU64( *(u_int64 *)ref );
}

/*---------------------------------------------------------------------------*/

#ifdef CM_HAVE_INT128
static inline void CM_SwapR128( void *ref )
{
	*(u_int128 *)ref = CM_SwapU128( *(u_int128 *)ref );
}
#endif /* CM_HAVE_INT128 */

/*---------------------------------------------------------------------------*/
/* Get Target Endianness                                                     */
/*---------------------------------------------------------------------------*/

static inline int CM_GetEndianness( void )
{
	return CM_BYTE_ORDER;
}

static inline bool8 CM_IsBigEndian( void )
{
	return (CM_BYTE_ORDER == CM_BIG_ENDIAN);
}

static inline bool8 CM_IsLilEndian( void )
{
	return (CM_BYTE_ORDER == CM_LIL_ENDIAN);
}

static inline bool8 CM_TestBigEndian( void )
{
	cmUnion32 test = {.u32 = 0x01FFFF00};
	return test.u8[0];
}

static inline bool8 CM_TestLilEndian( void )
{
	cmUnion32 test = {.u32 = 0x00FFFF01};
	return test.u8[0];
}

#endif /* END OF FILE */
