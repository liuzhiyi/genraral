#include <stdio.h>
#include "../includes/string.h"

int main() {
    u_char  *s1, *s2;

    s1 = "我是";
    s2 = "我是";
    printf("s1 and s2 compare value :%d\b", g_string_cmp(s1, g_string_len(s1), s2, g_string_len(s2)));
}

