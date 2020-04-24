/*
 *【 LibCM 】ver.20200423
 * Copyright (C) 2019 2020 J.Ingram
 * All Rights Reserved.
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
/* Combine 64/32/16-bit Values                                               */
/*---------------------------------------------------------------------------*/

#define CM_Set16w8( hi8, lo8 ) \
  (u16)( (((u16)hi8 << 8) & 0xFF00u) \
       | (((u16)lo8     ) & 0x00FFu) )

#define CM_Set32w16( hi16, lo16 ) \
  (u32)( (((u32)hi16 << 16) & 0xFFFF0000u) \
       | (((u32)lo16      ) & 0x0000FFFFu) )

#define CM_Set64w32( hi32, lo32 ) \
  (u64)( (((u64)hi32 << 32) & 0xFFFFFFFF00000000ull) \
       | (((u64)lo32      ) & 0x00000000FFFFFFFFull) )

/*---------------------------------------------------------------------------*/
/* Set Int128 with 32/16/8-bit Values                                        */
/*---------------------------------------------------------------------------*/

#define CM_Set128w8( dst, \
	hi8a, hi8b, hi8c, hi8d, hi8e, hi8f, hi8g, hi8h, \
	lo8a, lo8b, lo8c, lo8d, lo8e, lo8f, lo8g, lo8h ) \
\
	CM_Set128w16( dst, \
		CM_Set16w8( hi8a, hi8b ), CM_Set16w8( hi8c, hi8d ), \
		CM_Set16w8( hi8e, hi8f ), CM_Set16w8( hi8g, hi8h ), \
		CM_Set16w8( lo8a, lo8b ), CM_Set16w8( lo8c, lo8d ), \
		CM_Set16w8( lo8e, lo8f ), CM_Set16w8( lo8g, lo8h ) )

/*---------------------------------------------------------------------------*/

#define CM_Set128w16( dst, \
	hi16a, hi16b, hi16c, hi16d, \
	lo16a, lo16b, lo16c, lo16d ) \
\
	CM_Set128w32( dst, \
		CM_Set32w16( hi16a, hi16b ), CM_Set32w16( hi16c, hi16d ), \
		CM_Set32w16( lo16a, lo16b ), CM_Set32w16( lo16c, lo16d ) )

/*---------------------------------------------------------------------------*/

#define CM_Set128w32( dst, hi32a, hi32b, lo32a, lo32b ) \
\
	CM_Set128w64( dst, \
		CM_Set64w32( hi32a, hi32b ), \
		CM_Set64w32( lo32a, lo32b ) )

/*---------------------------------------------------------------------------*/
/* Set Int128 with 64-bit Values (x2)                                        */
/*---------------------------------------------------------------------------*/

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

#endif /* CM_HAVE_INT128 */
#endif /* END OF FILE */
