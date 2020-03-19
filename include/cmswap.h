/*
 *【 LibCM 】ver.20200314
 * Copyright (C) 2019 2020 J.Ingram
 * All rights reserved.
 */
/* cmswap.h
 * Endianness Utilities
 */
#ifndef INCLUDED_CMSWAP_H
#define INCLUDED_CMSWAP_H

#include "cmconf.h"
#include "cmtypes.h"

/*---------------------------------------------------------------------------*/
/* Public Interface                                                          */
/*---------------------------------------------------------------------------*/

/* --- ByteSwap for Integer Types (Unsigned) --- */

static inline u_int16 CM_SwapU16( u_int16 val );
static inline u_int32 CM_SwapU32( u_int32 val );
static inline u_int64 CM_SwapU64( u_int64 val );

#ifdef CM_HAVE_INT128
static inline u_int128 CM_SwapU128( u_int128 val );
#endif

/* --- ByteSwap for Integer Types (Signed) --- */

#define CM_SwapS16( val )  (s16)CM_SwapU16( (u16)val )
#define CM_SwapS32( val )  (s32)CM_SwapU32( (u32)val )
#define CM_SwapS64( val )  (s64)CM_SwapU64( (u64)val )

#ifdef CM_HAVE_INT128
#define CM_SwapS128( val )  (s128)CM_SwapU128( (u128)val )
#endif

/* --- ByteSwap for Floating Point Types --- */

static inline float32 CM_SwapF32( float32 val );
static inline float64 CM_SwapF64( float64 val );

#ifdef CM_HAVE_FLOAT128
static inline float128 CM_SwapF128( float128 val );
#endif

/* --- ByteSwap (Pass by Reference) --- */

static inline void CM_SwapR16( void *ref );
static inline void CM_SwapR32( void *ref );
static inline void CM_SwapR64( void *ref );

#ifdef CM_HAVE_INT128
static inline void CM_SwapR128( void *ref );
#endif

/* --- Get Target Endianness --- */

static inline int CM_GetEndianness( void );
static inline bool8 CM_IsBigEndian( void );
static inline bool8 CM_IsLilEndian( void );
static inline bool8 CM_TestBigEndian( void );
static inline bool8 CM_TestLilEndian( void );

/*---------------------------------------------------------------------------*/
/* ByteSwap for Integer Types                                                */
/*---------------------------------------------------------------------------*/
static inline u_int16 CM_SwapU16( u_int16 val )
{
	union16 in = {.u16 = val}, out;
	
	out.u8[0] = in.u8[1];
	out.u8[1] = in.u8[0];
	
	return out.u16;
}
/*---------------------------------------------------------------------------*/
static inline u_int32 CM_SwapU32( u_int32 val )
{
	union32 in = {.u32 = val}, out;
	
	out.u8[0] = in.u8[3];
	out.u8[1] = in.u8[2];
	out.u8[2] = in.u8[1];
	out.u8[3] = in.u8[0];
	
	return out.u32;
}
/*---------------------------------------------------------------------------*/
static inline u_int64 CM_SwapU64( u_int64 val )
{
	union64 in = {.u64 = val}, out;
	
	out.u8[0] = in.u8[7];
	out.u8[1] = in.u8[6];
	out.u8[2] = in.u8[5];
	out.u8[3] = in.u8[4];
	out.u8[4] = in.u8[3];
	out.u8[5] = in.u8[2];
	out.u8[6] = in.u8[1];
	out.u8[7] = in.u8[0];
	
	return out.u64;
}
/*---------------------------------------------------------------------------*/
#ifdef CM_HAVE_INT128
static inline u_int128 CM_SwapU128( u_int128 val )
{
	union128 in = {.u128 = val}, out;
	
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
	
	return out.u128;
}
#endif /* CM_HAVE_INT128 */

/*---------------------------------------------------------------------------*/
/* ByteSwap for Floating Point Types                                         */
/*---------------------------------------------------------------------------*/
static inline float32 CM_SwapF32( float32 val )
{
	union32 in = {.f32 = val}, out;
	
	out.u8[0] = in.u8[3];
	out.u8[1] = in.u8[2];
	out.u8[2] = in.u8[1];
	out.u8[3] = in.u8[0];
	
	return out.f32;
}
/*---------------------------------------------------------------------------*/
static inline float64 CM_SwapF64( float64 val )
{
	union64 in = {.f64 = val}, out;
	
	out.u8[0] = in.u8[7];
	out.u8[1] = in.u8[6];
	out.u8[2] = in.u8[5];
	out.u8[3] = in.u8[4];
	out.u8[4] = in.u8[3];
	out.u8[5] = in.u8[2];
	out.u8[6] = in.u8[1];
	out.u8[7] = in.u8[0];
	
	return out.f64;
}
/*---------------------------------------------------------------------------*/
#ifdef CM_HAVE_FLOAT128
static inline float128 CM_SwapF128( float128 val )
{
	union128 in = {.f128 = val}, out;
	
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
	
	return out.f128;
}
#endif /* CM_HAVE_FLOAT128 */

/*---------------------------------------------------------------------------*/
/* ByteSwap (Pass by Reference)                                              */
/*---------------------------------------------------------------------------*/
static inline void CM_SwapR16( void *ref )
{
	union16 *in = (union16 *)ref;
	union16 tmp = {.u16 = in->u16};
	
	in->u8[0] = tmp.u8[1];
	in->u8[1] = tmp.u8[0];
}
/*---------------------------------------------------------------------------*/
static inline void CM_SwapR32( void *ref )
{
	union32 *in = (union32 *)ref;
	union32 tmp = {.u32 = in->u32};
	
	in->u8[0] = tmp.u8[3];
	in->u8[1] = tmp.u8[2];
	in->u8[2] = tmp.u8[1];
	in->u8[3] = tmp.u8[0];
}
/*---------------------------------------------------------------------------*/
static inline void CM_SwapR64( void *ref )
{
	union64 *in = (union64 *)ref;
	union64 tmp = {.u64 = in->u64};
	
	in->u8[0] = tmp.u8[7];
	in->u8[1] = tmp.u8[6];
	in->u8[2] = tmp.u8[5];
	in->u8[3] = tmp.u8[4];
	in->u8[4] = tmp.u8[3];
	in->u8[5] = tmp.u8[2];
	in->u8[6] = tmp.u8[1];
	in->u8[7] = tmp.u8[0];
}
/*---------------------------------------------------------------------------*/
#ifdef CM_HAVE_INT128
static inline void CM_SwapR128( void *ref )
{
	union128 *in = (union128 *)ref;
	union128 tmp = {.u128 = in->u128};
	
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

/* Alternate methods for testing the target machine's endianness.
 * The byte at the lowest address is returned as a truth value.
 */
static inline bool8 CM_TestBigEndian( void )
{
	union32 test = {.u32 = 0x01FFFF00};
	return test.u8[0];
}

static inline bool8 CM_TestLilEndian( void )
{
	union32 test = {.u32 = 0x00FFFF01};
	return test.u8[0];
}

#endif /* END OF FILE */
