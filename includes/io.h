#ifndef _IO_H_
#define _IO_H_
#include "../includes/os.h"
#include "../includes/array.h"

#define  maxConsecutiveEmptyReads  100

typedef  void*     g_fd_pt;
typedef int (*g_read_pt)(g_fd_pt, g_list_t);
typedef int (*g_write_pt)(g_fd_pt, g_list_t);

typedef struct g_reader_s {
    g_list_t     buf;
    g_fd_pt      fd;
    g_read_pt    read;
    int          r;
    int          w;
} g_reader_t;

typdef struct g_writer_s {
    g_list_t     buf;
    g_fd_pt      fd;
    g_write_pt   write;
} g_writer_t;

#endif
