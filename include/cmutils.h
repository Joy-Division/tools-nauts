/*
 *【 LibCM 】ver.20200504
 * Copyright (C) 2019 2020 J.Ingram
 * All Rights Reserved.
 */
#ifndef INCLUDED_CMUTILS_H
#define INCLUDED_CMUTILS_H

/*===========================================================================*/
/* File & Directory Utils                                                    */
/*===========================================================================*/
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
