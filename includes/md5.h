#ifndef _H_MD5_H_
#define _H_MD5_H_
#inlcude "os.h"

typedef struct {
    uint64_t  bytes;
    uint32_t  a, b, c, d;
    u_char    buffer[64];
} md5_ctx;

void MD5_Init(ngx_md5_t *ctx);
void MD5_Update(ngx_md5_t *ctx, const void *data, size_t size);
void MD5_Final(u_char result[16], ngx_md5_t *ctx);

#endif
