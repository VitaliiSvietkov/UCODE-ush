#include "../inc/libmx.h"

void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n) {
    unsigned char *dst_tmp = dst;
    const unsigned char *src_tmp = src;
    while (n > 0) {
        *dst_tmp = *src_tmp;
        if (*dst_tmp == c) {
            dst_tmp++;
            return dst_tmp;
        }
        dst_tmp++;
        src_tmp++;
        n--;
    }
    return NULL;
}

