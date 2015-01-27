/*算法说明： sha1要求是BIG-ENDIAN
 *输入的字符串按二进制字符串处理分成n组，每组有512位，最后一组
 *如果小于448位，补上0x80,最后64位放入消息长度（注意：所以消
 *息长度要小于2^64位，md5与此稍有不同）;如果大于448位，那么这个分组后面补0，进行一次摘要运算，
 *然后再建立一个分组，前面全部补0，最后16个字节放长度，再进行一次摘要。处理每个分组需要80个步骤处理
 *之前需要初始化常量hash组共160位，将每个分组分成16个字（为4个字节）
 *一次排序（从0开始计数），对于位于16到79令W[t] = S1(W[t-3] XOR W[t-8] XOR W[t- 14] XOR W[t-16]).
 *令 A = H0, B = H1, C = H2, D = H3, E = H4.对于 t = 0 到 79，执行下面的循环
 *TEMP = S5(A) + ft(B,C,D) + E + Wt + Kt;E = D; D = C; C = S30(B); B = A; A = TEMP
 *令 H0 = H0 + A, H1 = H1 + B, H2 = H2 + C, H3 = H3 + D, H4 = H4 + E.以此处理剩余的分组。
 *最终得到消息摘要H0,H1,H2,H3,H5
 *以下是一些函数常量说明：Sn(X) = (X<<n)OR(X>>32-n)字移位操作
 *一系列的常量字K(0), K(1), ... , K(79)，如果以16进制给出。它们如下：
 *Kt = 0x5A827999 (0 <= t <= 19)
 *Kt = 0x6ED9EBA1 (20 <= t <= 39)
 *Kt = 0x8F1BBCDC (40 <= t <= 59)
 *Kt = 0xCA62C1D6 (60 <= t <= 79).
 *在SHA1中我们需要一系列的函数。每个函数ft (0 <= t <= 79)都操作32位字B，C，D并且产生32位字作为输出。ft(B,C,D)
 *ft(B,C,D) = (B AND C) or ((NOT B) AND D) ( 0 <= t <= 19)
 *ft(B,C,D) = B XOR C XOR D (20 <= t <= 39)
 *ft(B,C,D) = (B AND C) or (B AND D) or (C AND D) (40 <= t <= 59)
 *ft(B,C,D) = B XOR C XOR D (60 <= t <= 79).
 *
 */

#include "../includes/sha1.h"

//汇编语言版
extern void sha1_core(uint32_t *hash, const unsigned char *p,
              unsigned int nblocks);

int SHA1_Init(sha_ctx *c) {
    c->hash[0] = 0x67452301;
    c->hash[1] = 0xEFCDAB89;
    c->hash[2] = 0x98BADCFE;
    c->hash[3] = 0x10325476;
    c->hash[4] = 0xC3D2E1F0;
    c->len = 0;
    c->cnt = 0;
    return 0;
}

int SHA1_Update(sha_ctx *c, const void *ptr, unsigned long n) {
    unsigned long nb;
    const unsigned char *p = ptr;

    c->len += n << 3;
    while (n != 0) {
        if (c->cnt || n < 64) {
            nb = 64 - c->cnt;
            if (nb > n)
                nb = n;
            memcpy(&c->buf.b[c->cnt], p, nb);
            if ((c->cnt += nb) == 64) {
                sha1_core(c->hash, c->buf.b, 1);
                c->cnt = 0;
            }
        } else {
            nb = n >> 6;
            sha1_core(c->hash, p, nb);
            nb <<= 6;
        }
        n -= nb;
        p += nb;
    }
    return 0;
}

int SHA1_Final(unsigned char *hash, sha_ctx *c) {
    unsigned int cnt = c->cnt;

    c->buf.b[cnt++] = 0x80;    //加上结束标志位
    if (cnt > 56) {
        if (cnt < 64)
            memset(&c->buf.b[cnt], 0, 64 - cnt);
        sha1_core(c->hash, c->buf.b, 1);
        cnt = 0;
    }
    if (cnt < 56)
        memset(&c->buf.b[cnt], 0, 56 - cnt);
    c->buf.l[7] = c->len;             //加上消息长度值
    sha1_core(c->hash, c->buf.b, 1);
    memcpy(hash, c->hash, 20);
    return 0;
}

//C语言版
void sha1_core_c(uint32_t *hash, const unsigned char *p,
              unsigned int nblocks) {
    uint32_t wblock[80];
    register uint32_t a, b, c, d, e, temp;
    size_t   t;

    memcpy(p, wblock, 64);

    for (t = 16; t < 80; t++) {
        wblock[t] = ROLT(wblock[t-3] ^ wblock[t-8] ^ wblock[t- 14] ^ wblock[t-16], 1);
    }

    a = hash[0];
    b = hash[1];
    c = hash[2];
    d = hash[3];
    e = hash[4];

    for(t = 0; t < 20; t++) {
        temp = ROLT(a, 5) + ROUND1(b,c,d) + e + wblock[t] + 0x5A827999;
        e = d;
        d = c;
        c = ROLT(b, 30);
        b = a;
        a = temp;
    }

    for(t = 20; t < 40; t++) {
        temp = ROLT(a, 5) + ROUND2(b,c,d) + e + wblock[t] + 0x6ED9EBA1;
        e = d;
        d = c;
        c = ROLT(b, 30);
        b = a;
        a = temp;
    }

    for(t = 40; t < 60; t++) {
        temp = ROLT(a, 5) + ROUND3(b,c,d) + e + wblock[t] + 0x8F1BBCDC;
        e = d;
        d = c;
        c = ROLT(b, 30);
        b = a;
        a = temp;
    }

    for(t = 60; t < 80; t++) {
        temp = ROLT(a, 5) + ROUND4(b,c,d) + e + wblock[t] + 0xCA62C1D6;
        e = d;
        d = c;
        c = ROLT(b, 30);
        b = a;
        a = temp;
    }

    hash[0] += a;
    hash[1] += b;
    hash[2] += c;
    hash[3] += d;
    hash[4] += e;
}
