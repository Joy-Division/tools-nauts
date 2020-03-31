/*
 *【 LibCM 】ver.20200331
 * Copyright (C) 2019 2020 J.Ingram
 * All rights reserved.
 */
/* cmdebug.h
 * Debugging Utilities
 */
#ifndef INCLUDED_CMDEBUG_H
#define INCLUDED_CMDEBUG_H

#include <stdlib.h> /* for exit(), abort() */
#include <stdio.h>  /* for printf(), puts() */

#if !defined(NDEBUG)

/*---------------------------------------------------------------------------*/
/* Internal Procedures                                                       */
/*---------------------------------------------------------------------------*/
#define CM_ErrExpr( expr_str ) \
	printf( "*** %s:%u in %s(), '%s' failed!\n", \
	__FILE__, __LINE__, __FUNCTION__, expr_str )

#define CM_ErrMessage( msg_str ) \
	puts( "*** " msg_str )

/*---------------------------------------------------------------------------*/
/* Standard Assertion                                                        */
/*---------------------------------------------------------------------------*/
#define CM_Assert( expr ) \
	((void)((expr) ? 0 : (CM_ErrExpr(#expr), abort(), 0)))

#define CM_AssertWarn( expr ) \
	((void)((expr) ? 0 : (CM_ErrExpr(#expr), 0)))

#define CM_AssertExit( expr ) \
	((void)((expr) ? 0: (CM_ErrExpr(#expr), exit(1), 0)))

/*---------------------------------------------------------------------------*/
/* Assertion with Message                                                    */
/*---------------------------------------------------------------------------*/
#define CM_AssertMsg( expr, msg ) \
	((void)((expr) ? 0 : (CM_ErrExpr(#expr), CM_ErrMessage(msg), abort(), 0)))

#define CM_AssertMsgWarn( expr, msg ) \
	((void)((expr) ? 0 : (CM_ErrExpr(#expr), CM_ErrMessage(msg), 0)))

#define CM_AssertMsgExit( expr, msg ) \
	((void)((expr) ? 0 : (CM_ErrExpr(#expr), CM_ErrMessage(msg), exit(1), 0)))

/*---------------------------------------------------------------------------*/
/* Dummy Definitions for NDEBUG                                              */
/*---------------------------------------------------------------------------*/
#else /* !NDEBUG */

#define CM_Assert( expr )              ((void)0)
#define CM_AssertWarn( expr )          ((void)0)
#define CM_AssertExit( expr )          ((void)0)

#define CM_AssertMsg( expr, msg )      ((void)0)
#define CM_AssertMsgWarn( expr, msg )  ((void)0)
#define CM_AssertMsgExit( expr, msg )  ((void)0)

#endif /* !NDEBUG */

#endif /* END OF FILE */
