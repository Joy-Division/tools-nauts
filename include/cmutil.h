/*
 *【 LibCM 】by J.Ingram
 * Common Utilities
 */
#ifndef INC_CMUTIL_H
#define INC_CMUTIL_H

#include <stddef.h> /* for size_t */

/*---------------------------------------------------------------------------*/
/* Size Macros                                                               */
/*---------------------------------------------------------------------------*/
#define CM_KBtoBYTE(x)  (size_t)((x) << 10)
#define CM_MBtoBYTE(x)  (size_t)((x) << 20)
#define CM_GBtoBYTE(x)  (size_t)((x) << 30)

/* Will always round down if !( x >= n ) */
#define CM_BYTEtoKB(x)  (size_t)((x) >> 10)
#define CM_BYTEtoMB(x)  (size_t)((x) >> 20)
#define CM_BYTEtoGB(x)  (size_t)((x) >> 30)

/*---------------------------------------------------------------------------*/
/* File & Directory Utils                                                    */
/*---------------------------------------------------------------------------*/
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
/* vim: set noet ts=4 sw=4 ft=c ff=unix fenc=utf-8 : */
