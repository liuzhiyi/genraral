#ifndef _OS_H_
#define _OS_H_

#define WIN32

#ifdef WIN32
#include <windows.h>
typedef unsigned __int32         uint32_t;
typedef unsigned long __int32    uint64_t;
typedef unsigned int             uint_t;
#elif defined LINUX

#endif

#define EOS          '\0'      //end of string

#define g_malloc         malloc
#define g_free           free
#define g_alloc          alloc
#define g_callo          calloc
#define g_realloc        realloc
#define g_log_error(s)
#define g_log_notice(s)  printf(s)
#define g_debug(s)

#endif
