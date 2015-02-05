#ifndef _IO_H_
#define _IO_H_
#include "../includes/os.h"
#include "../includes/array.h"

typedef  void*     g_fd_pt;
typedef int (*g_read_pt)();

typedef struct g_reader_s {
    g_array_t    buf;
    g_fd_pt      fd;
    g_read_pt    read;
    int          r;
    int          w;
} g_reader_t;
#endif
