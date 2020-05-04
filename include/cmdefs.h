/*
 *【 LibCM 】ver.20200504
 * Copyright (C) 2019 2020 J.Ingram
 * All Rights Reserved.
 */
#ifndef INCLUDED_CMDEFS_H
#define INCLUDED_CMDEFS_H

/*===========================================================================*/
/* Generic Constant Definitions                                              */
/*===========================================================================*/

/* --- Logical Constants (Boolean) --- */

#define CM_TRUE   (1)
#define CM_FALSE  (0)

/* These macros are copied from "cmtypes.h" to avoid
 * creating a dependency on this header or vice versa.
 */
#ifndef TRUE       /* Duplicately defined in "cmtypes.h" */
#define TRUE  (1)  /* Any changes must be synchronized.  */
#endif
#ifndef FALSE      /* Duplicately defined in "cmtypes.h" */
#define FALSE (0)  /* Any changes must be synchronized.  */
#endif

/* --- Logical Constants (Confirmation) --- */

#define CM_YES  (1)
#define CM_NO   (0)

#ifndef YES
#define YES CM_YES
#endif
#ifndef NO
#define NO  CM_NO
#endif

/* --- Status Constants --- */

#define CM_ON   (1)
#define CM_OFF  (0)

#ifndef ON
#define ON  CM_ON
#endif
#ifndef OFF
#define OFF CM_OFF
#endif

/* --- Result Constants --- */

#define CM_OK  ( 0)
#define CM_NG  (-1)

#ifndef OK
#define OK  CM_OK
#endif
#ifndef NG
#define NG  CM_NG
#endif

/*===========================================================================*/
/* C Language Standard                                                       */
/*===========================================================================*/

#if defined(__STDC__)
#  define CM_STD_C89 __STDC__
#  if defined(__STDC_VERSION__)
#    define CM_STD_C __STDC_VERSION__
#    if (__STDC_VERSION__ >= 199409L)
#      define CM_STD_C95 199409L
#    endif
#    if (__STDC_VERSION__ >= 199901L)
#      define CM_STD_C99 199901L
#    endif
#    if (__STDC_VERSION__ >= 201112L)
#      define CM_STD_C11 201112L
#    endif
#    if (__STDC_VERSION__ >= 201710L)
#      define CM_STD_C18 201710L
#    endif
#  endif
#endif

/*===========================================================================*/
/* C++ Language Standard                                                     */
/*===========================================================================*/

#if defined(__cplusplus)
#  define CM_STD_CPP __cplusplus
#  if (__cplusplus >= 199711L)
#    define CM_STD_CPP98 199711L
#  endif
#  if (__cplusplus >= 201103L)
#    define CM_STD_CPP11 201103L
#  endif
#  if (__cplusplus >= 201402L)
#    define CM_STD_CPP14 201402L
#  endif
#  if (__cplusplus >= 201703L)
#    define CM_STD_CPP17 201703L
#  endif
#endif

#endif /* END OF FILE */
