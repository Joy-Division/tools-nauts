/*
 *【 LibCM 】ver.20200504
 * Copyright (C) 2019 2020 J.Ingram
 * All Rights Reserved.
 */
#ifndef INCLUDED_CMMATH_H
#define INCLUDED_CMMATH_H

#include "cmtypes.h"

/*===========================================================================*/
/* Simple Evaluations                                                        */
/*===========================================================================*/

#define CM_IsNumOdd( num )   (!!((num) & 1))
#define CM_IsNumEven( num )  ( !((num) & 1))

#define CM_Divisible( numer, denom )  (!( numer % denom ))

/*===========================================================================*/
/* Multiples of Bytes (in KiB, MiB, GiB, etc.)                               */
/*===========================================================================*/

#define CM_KBtoBYTE( num )  ((u_long64)(num) << 10)
#define CM_MBtoBYTE( num )  ((u_long64)(num) << 20)
#define CM_GBtoBYTE( num )  ((u_long64)(num) << 30)
#define CM_TBtoBYTE( num )  ((u_long64)(num) << 40)

/* rounds down if( !!(x % 1024) ) */
#define CM_BYTEtoKB( num )  ((u_long64)(num) >> 10)
#define CM_BYTEtoMB( num )  ((u_long64)(num) >> 20)
#define CM_BYTEtoGB( num )  ((u_long64)(num) >> 30)
#define CM_BYTEtoTB( num )  ((u_long64)(num) >> 40)

#endif /* END OF FILE */
