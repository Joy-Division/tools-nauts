/*
 *【 LibCM 】by J.Ingram
 * Debugging Utilities
 */
#ifndef INC_CMDEBUG_H
#define INC_CMDEBUG_H

#include <stdio.h>  /* for printf() */
#include <stdlib.h> /* for exit(), abort() */

#if !defined( CM_NODEBUG )

/*---------------------------------------------------------------------------*
 * Assertion Macros
 *---------------------------------------------------------------------------*/
#define CM_ASSERT( expr )                                   \
{                                                           \
    if( !(expr) ){                                          \
        printf( "%s() in %s:%u, assertion '%s' failed!\n",  \
            __FUNCTION__, __FILE__, __LINE__, #expr );      \
        abort();                                            \
    }                                                       \
}

#define CM_ASSERT_MSG( expr, msg )                          \
{                                                           \
    if( !(expr) ){                                          \
        printf( "%s() in %s:%u, assertion '%s' failed!\n",  \
            __FUNCTION__, __FILE__, __LINE__, #expr );      \
        printf( msg "\n" );                                 \
        abort();                                            \
    }                                                       \
}

#define CM_ASSERT_WARN( expr )                              \
{                                                           \
    if( !(expr) ){                                          \
        printf( "%s() in %s:%u, assertion '%s' failed!\n",  \
            __FUNCTION__, __FILE__, __LINE__, #expr );      \
    }                                                       \
}

#define CM_ASSERT_WARN_MSG( expr, msg )                     \
{                                                           \
    if( !(expr) ){                                          \
        printf( "%s() in %s:%u, assertion '%s' failed!\n",  \
            __FUNCTION__, __FILE__, __LINE__, #expr );      \
        printf( msg "\n" );                                 \
    }                                                       \
}

#define CM_ASSERT_EXIT( expr )                              \
{                                                           \
    if( !(expr) ){                                          \
        printf( "%s() in %s:%u, assertion '%s' failed!\n",  \
            __FUNCTION__, __FILE__, __LINE__, #expr );      \
        exit(1);                                            \
    }                                                       \
}

#define CM_ASSERT_EXIT_MSG( expr, msg )                     \
{                                                           \
    if( !(expr) ){                                          \
        printf( "%s() in %s:%u, assertion '%s' failed!\n",  \
            __FUNCTION__, __FILE__, __LINE__, #expr );      \
        printf( msg "\n" );                                 \
        exit(1);                                            \
    }                                                       \
}

/*---------------------------------------------------------------------------*
 * Dummy Definitions for CM_NODEBUG
 *---------------------------------------------------------------------------*/
#else /* !CM_NODEBUG */

#define CM_ASSERT(...)
#define CM_ASSERT_MSG(...)
#define CM_ASSERT_WARN(...)
#define CM_ASSERT_WARN_MSG(...)
#define CM_ASSERT_EXIT(...)
#define CM_ASSERT_EXIT_MSG(...)

#endif /* !CM_NODEBUG */
/*---------------------------------------------------------------------------*/
#endif /* END OF FILE */
/*---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: c; -*- */
/* vim: set noet ts=4 sw=4 ft=c ff=dos fenc=utf-8 : */
