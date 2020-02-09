/*
 *【 LibCM 】by J.Ingram
 * Endianness Utilities
 */
#ifndef INC_CMSWAP_H
#define INC_CMSWAP_H

#include "cmtypes.h"

/*---------------------------------------------------------------------------*/
/* Public Definitions                                                        */
/*---------------------------------------------------------------------------*/
#define CM_ENDIAN_ID_LE  'L'  /* Unique ID for Little Endian */
#define CM_ENDIAN_ID_BE  'B'  /* Unique ID for Big Endian    */

/*---------------------------------------------------------------------------*/
/* Public Interface                                                          */
/*---------------------------------------------------------------------------*/

/* --- Reverse Endianness for Integer Types --- */

static inline uint16 CM_SwapU16( uint16 val );
static inline uint32 CM_SwapU32( uint32 val );
static inline uint64 CM_SwapU64( uint64 val );

#ifdef CM_HAVE_INT128
static inline uint128 CM_SwapU128( uint128 val );
#endif

#define CM_SwapS16(val)  (s16)CM_SwapU16((u16)val)
#define CM_SwapS32(val)  (s32)CM_SwapU32((u32)val)
#define CM_SwapS64(val)  (s64)CM_SwapU64((u64)val)

#ifdef CM_HAVE_INT128
#define CM_SwapS128(val)  (s128)CM_SwapU128((u128)val)
#endif

/* --- Reverse Endianness for Floating Point Types --- */

static inline float32 CM_SwapF32( float32 val );
static inline float64 CM_SwapF64( float64 val );

#if CM_HAVE_FLOAT128
static inline float128 CM_SwapF128( float128 val );
#endif

/* --- Reverse Endianness (Pass by Reference) --- */

static inline void CM_SwapR16( void *ref );
static inline void CM_SwapR32( void *ref );
static inline void CM_SwapR64( void *ref );

#ifdef CM_HAVE_INT128
static inline void CM_SwapR128( void *ref );
#endif

/* --- Get Target Endianness --- */

static inline u_byte CM_IsBigEndian( void );
static inline u_byte CM_IsLittleEndian( void );

/*---------------------------------------------------------------------------*/
/* Reverse Endianness for Integer Types                                      */
/*---------------------------------------------------------------------------*/
static inline uint16 CM_SwapU16( uint16 val )
{
	union16 in = {.u16 = val}, out;
	
	out.u8[0] = in.u8[1];
	out.u8[1] = in.u8[0];
	
	return out.u16;
}
/*---------------------------------------------------------------------------*/
static inline uint32 CM_SwapU32( uint32 val )
{
	union32 in = {.u32 = val}, out;
	
#ifdef CM_CHAIN_BYTESWAP
	out.u16[0] = CM_SwapU16( in.u16[1] );
	out.u16[1] = CM_SwapU16( in.u16[0] );
#else
	out.u8[0] = in.u8[3];
	out.u8[1] = in.u8[2];
	out.u8[2] = in.u8[1];
	out.u8[3] = in.u8[0];
#endif
	return out.u32;
}
/*---------------------------------------------------------------------------*/
static inline uint64 CM_SwapU64( uint64 val )
{
	union64 in = {.u64 = val}, out;
	
#ifdef CM_CHAIN_BYTESWAP
	out.u32[0] = CM_SwapU32( in.u32[1] );
	out.u32[1] = CM_SwapU32( in.u32[0] );
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
/*---------------------------------------------------------------------------*/
#ifdef CM_HAVE_INT128
static inline uint128 CM_SwapU128( uint128 val )
{
	union128 in = {.u128 = val}, out;
	
#ifdef CM_CHAIN_BYTESWAP
	out.u64[0] = CM_SwapU64( in.u64[1] );
	out.u64[1] = CM_SwapU64( in.u64[0] );
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
#endif /* CM_HAVE_INT128 */

/*---------------------------------------------------------------------------*/
/* Reverse Endianness for Floating Point Types                               */
/*---------------------------------------------------------------------------*/
static inline float32 CM_SwapF32( float32 val )
{
	union32 in = {.f32 = val}, out;
	
#ifdef CM_CHAIN_BYTESWAP
	out.u16[0] = CM_SwapU16( in.u16[1] );
	out.u16[1] = CM_SwapU16( in.u16[0] );
#else
	out.u8[0] = in.u8[3];
	out.u8[1] = in.u8[2];
	out.u8[2] = in.u8[1];
	out.u8[3] = in.u8[0];
#endif
	return out.f32;
}
/*---------------------------------------------------------------------------*/
static inline float64 CM_SwapF64( float64 val )
{
	union64 in = {.f64 = val}, out;
	
#ifdef CM_CHAIN_BYTESWAP
	out.u32[0] = CM_SwapU32( in.u32[1] );
	out.u32[1] = CM_SwapU32( in.u32[0] );
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
/*---------------------------------------------------------------------------*/
#ifdef CM_HAVE_INT128
static inline float128 CM_SwapF128( float128 val )
{
	union128 in = {.f128 = val}, out;
	
#ifdef CM_CHAIN_BYTESWAP
	out.u64[0] = CM_SwapU64( in.u64[1] );
	out.u64[1] = CM_SwapU64( in.u64[0] );
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
#endif /* CM_HAVE_FLOAT128 */

/*---------------------------------------------------------------------------*/
/* Reverse Endianness (Pass by Reference)                                    */
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
#define MSB1_LSB0 0x01FFFF00u
#define MSB0_LSB1 0x00FFFF01u

/* The MSB is set to 0x01 (TRUE) and the LSB is set to 0x00 (FALSE).
 * Because Big Endian architectures store the MSB at the lowest address,
 * the first element of the byte array is returned as a truth value. */
static inline u_byte CM_IsBigEndian( void )
{
	union32 test = {.u32 = MSB1_LSB0};
	return test.u8[0];
}

/* The MSB is set to 0x00 (FALSE) and the LSB is set to 0x01 (TRUE).
 * Because Little Endian architectures store the LSB at the lowest address,
 * the first element of the byte array is returned as a truth value. */
static inline u_byte CM_IsLittleEndian( void )
{
	union32 test = {.u32 = MSB0_LSB1};
	return test.u8[0];
}

#undef MSB1_LSB0
#undef MSB0_LSB1

/*---------------------------------------------------------------------------*/
#endif /* END OF FILE */
/*---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: c; -*- */
/* vim: set noet ts=4 sw=4 ft=c ff=unix fenc=utf-8 : */
