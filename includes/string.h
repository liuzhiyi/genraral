#ifndef _STRING_H_
#define _STRING_H_
#include "../includes/os.h"

#define   PRIME_RK     16777619

#define  g_char_tolower(c)    (u_char) ((c >= 'A' && c <= 'Z') ? (c | 0x20) : c)
#define  g_char_toupper(c)    (u_char) ((c >= 'a' && c <= 'z') ? (c & ~0x20) : c)

int g_string_cmp(u_char *s1, uint_t s1_n, u_char *s2, uint_t s2_n);
int g_string_len(u_char *s);

#endif
