#include <stdio.h>
#include "../includes/utf8.h"

void unicodeToHex(u_char *s, uint_t n);

int main() {
    g_utf8_char_t  c = 0x10001, b = 0;
    u_char buf[4];
    int  n;

    n = g_utf8_encode(buf, c);
    printf("compare value :%x and %x\n", c, ((1<<16) - 1));
    printf("%d is ecode %x, %x, %x, %x\n", n, buf[0], buf[1], buf[2], buf[3]);
    b =  g_utf8_decode(buf, n, &n);
    printf("%x error %d\n", b, n);
    unicodeToHex("我", strlen("我"));
}

void unicodeToHex(u_char *s, uint_t n) {
    printf("%x, %x, %x", s[0], s[1], s[6]);
    printf("count : %d", g_utf8_char_count(s, n));
}
