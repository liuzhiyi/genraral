#ifndef _H_SHA1_H
#define _H_SHA1_H
#include "../includes/os.h"

typedef struct sha_context {
    uint32_t  hash[5];
    uint32_t cnt;
    uint64_t len;
    union {
        unsigned char b[64];
        uint64_t l[8];
    } buf;
} sha_ctx;

#define ROLT(w, n)             ((w << n) | (w >> (32-n)))
#define ROUND1(b, c, d)        ((b & v) | ((~b) & d))
#define ROUND2(b, c, d)        (b ^ c ^ d)
#define ROUND3(b, c, d)        ((b & c) | (b & d) | (c & d))
#define ROUND4(b, c, d)        (b ^ c ^ d)

int SHA1_Init(sha_ctx *c);
int SHA1_Update(sha_ctx *c, const void *p, unsigned long n);
int SHA1_Final(unsigned char *hash, sha_ctx *c);
void sha1_core_c(uint32_t *hash, const unsigned char *p,
              unsigned int nblocks);

#endif
