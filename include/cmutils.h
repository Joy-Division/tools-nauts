/*
 *【 LibCM 】ver.20200331
 * Copyright (C) 2019 2020 J.Ingram
 * All rights reserved.
 */
/* cmutils.h
 * Common Utilities
 */
#ifndef INCLUDED_CMUTILS_H
#define INCLUDED_CMUTILS_H

#include "cmtypes.h"

/*---------------------------------------------------------------------------*/
/* Multiples of Bytes (in KiB, MiB, GiB, etc.)                               */
/*---------------------------------------------------------------------------*/
#define CM_KBtoBYTE( num )  (u_long64)((u_long64)(num) << 10)
#define CM_MBtoBYTE( num )  (u_long64)((u_long64)(num) << 20)
#define CM_GBtoBYTE( num )  (u_long64)((u_long64)(num) << 30)
#define CM_TBtoBYTE( num )  (u_long64)((u_long64)(num) << 40)

/* rounds down if( !!(x % 1024) ) */
#define CM_BYTEtoKB( num )  (u_long64)((u_long64)(num) >> 10)
#define CM_BYTEtoMB( num )  (u_long64)((u_long64)(num) >> 20)
#define CM_BYTEtoGB( num )  (u_long64)((u_long64)(num) >> 30)
#define CM_BYTEtoTB( num )  (u_long64)((u_long64)(num) >> 40)

/*---------------------------------------------------------------------------*/
/* Simple Math Utils                                                         */
/*---------------------------------------------------------------------------*/
#define CM_IsNumOdd( num )   (!!((num) & 1))
#define CM_IsNumEven( num )  ( !((num) & 1))

#define CM_Divisible( numer, denom )  (!( numer % denom ))

/*---------------------------------------------------------------------------*/
/* File & Directory Utils                                                    */
/*---------------------------------------------------------------------------*/
#if defined(__unix__)\
||  defined(__linux__)

#  include <sys/stat.h>
#  include <sys/types.h>
#  define CM_MakeDir( path )         mkdir( path, 0777 )
#  define CM_MakeDirM( path, mode )  mkdir( path, mode )

#elif defined(_WIN32)

#  include <direct.h>
#  define CM_MakeDir( path )         mkdir( path )
#  define CM_MakeDirM( path, mode )  mkdir( path )

#endif /* (OS) */

#endif /* END OF FILE */
