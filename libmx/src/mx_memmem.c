#include "../inc/libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len) {
    if (big_len < little_len || little_len == 0 || big_len == 0)
        return NULL;
    const unsigned char *little_tmp = little;
    const unsigned char *big_tmp = big;
    unsigned char *res = (unsigned char *)malloc(little_len);
    while (big_len >= little_len) {
        mx_memcpy(res, big_tmp, little_len);
        if (!mx_memcmp(res, little_tmp, little_len))
            return res;
        big_tmp++;
        big_len--;
    }
    free(res);
    return NULL;
}

