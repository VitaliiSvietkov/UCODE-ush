#include "../inc/libmx.h"

void *mx_memrchr(const void *s, int c, size_t n) {
    unsigned char *s_tmp = (unsigned char *)malloc(n);
    unsigned char *start = s_tmp;
    mx_memcpy(s_tmp, s, n);
    for (size_t i = 0; i < n; i++)
        s_tmp++;
    while (n > 0) {
        if (*s_tmp == c)
            return s_tmp;
        s_tmp--;
        n--;
    }
    free(start);
    return NULL;
}

