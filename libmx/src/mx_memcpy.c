#include "../inc/libmx.h"

void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n) {
    unsigned char *res = dst;
    const unsigned char *src_tmp = src;
    while (n > 0) {
        *res = *src_tmp;
        n--;
        res++;
        src_tmp++;
    }
    return dst;
}

