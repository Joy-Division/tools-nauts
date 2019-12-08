/*
 *【 LibCM 】by J.Ingram
 * Common Definitions
 */
#ifndef INC_CMDEFS_H
#define INC_CMDEFS_H

/*---------------------------------------------------------------------------*/
/* Result/Status Macros                                                      */
/*---------------------------------------------------------------------------*/
#ifndef NO
#define NO  (0)
#endif
#ifndef YES
#define YES (1)
#endif

#ifndef OFF
#define OFF (0)
#endif
#ifndef ON
#define ON  (1)
#endif

#ifndef NG
#define NG  (-1)
#endif
#ifndef OK
#define OK  (0)
#endif

/*---------------------------------------------------------------------------*/
/* C/C++ Language Version                                                    */
/*---------------------------------------------------------------------------*/

/* for C */
#if defined( __STDC__ )
#  define STANDARD_C89 __STDC__
#  if defined( __STDC_VERSION__ )
#    define STANDARD_C __STDC_VERSION__
#    if ( __STDC_VERSION__ >= 199409L )
#      define STANDARD_C95 199409L
#    endif
#    if ( __STDC_VERSION__ >= 199901L )
#      define STANDARD_C99 199901L
#    endif
#    if ( __STDC_VERSION__ >= 201112L )
#      define STANDARD_C11 201112L
#    endif
#    if ( __STDC_VERSION__ >= 201710L )
#      define STANDARD_C18 201710L
#    endif
#  endif
#endif

/* for C++ */
#if defined( __cplusplus )
#  define STANDARD_CPP __cplusplus
#  if ( __cplusplus >= 199711L )
#    define STANDARD_CPP98 199711L
#  endif
#  if ( __cplusplus >= 201103L )
#    define STANDARD_CPP11 201103L
#  endif
#  if ( __cplusplus >= 201402L )
#    define STANDARD_CPP14 201402L
#  endif
#  if ( __cplusplus >= 201703L )
#    define STANDARD_CPP17 201703L
#  endif
#endif

/*---------------------------------------------------------------------------*/
#endif /* END OF FILE */
/*---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: c; -*- */
/* vim: set noet ts=4 sw=4 ft=c ff=unix fenc=utf-8 : */
