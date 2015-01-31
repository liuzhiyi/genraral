#ifndef _UTF8_H_
#define _UTF8_H_
#include "../includes/os.h"

typedef unsigned long     g_utf8_char_t;

#define UTF8_ERROR        0xFFFD
#define UTF8_SELF         0X80               //小于0x80都是一个词
#define MAX_UTF8          0x0010FFFF         //最大能表示的词
#define UTFMax            4                  //utf8一个词最大字节数

#define    SURROGATE_MIN   0xD800
#define    SURROGATE_MAX   0xDFFF

#define    UTF8_T1  0x00                   // 0000 0000
#define    UTF8_TX  0x80 // 1000 0000
#define    UTF8_T2  0xC0 // 1100 0000
#define    UTF8_T3  0xE0 // 1110 0000
#define    UTF8_T4  0xF0 // 1111 0000
#define    UTF8_T5  0xF8 // 1111 1000

#define    UTF8_MASKX  0x3F // 0011 1111
#define    UTF8_MASK2  0x1F // 0001 1111
#define    UTF8_MASK3  0x0F // 0000 1111
#define    UTF8_MASK4  0x07 // 0000 0111

#define    UTF8_W1Max  ((1<<7) - 1)
#define    UTF8_W2Max  ((1<<11) - 1)
#define    UTF8_W3Max  ((1<<16) - 1)

int g_utf8_char_count(u_char *s, uint_t n);
int g_utf8_encode(u_char *s, g_utf8_char_t c);
int g_utf8_char_len(g_utf8_char_t c);
int g_utf8_full_char(u_char *s, uint_t n);
g_utf8_char_t g_utf8_decode(u_char *s, uint_t n, int *size);

#endif
