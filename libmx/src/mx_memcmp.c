#include "../inc/libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t n) {
    if (n == 0)
        return 0;
    const unsigned char *s1_tmp = s1;
    const unsigned char *s2_tmp = s2;
    while (n > 0) {
        if (*s1_tmp != *s2_tmp) {
            return *s1_tmp - *s2_tmp;
        }
        s1_tmp++;
        s2_tmp++;
        n--;
    }
    return 0;
}

