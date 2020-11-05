#include "../inc/libmx.h"

void *mx_memset(void *b, int c, size_t len) {
    unsigned char *ptr = b;
    while (len > 0) {
        *ptr = c;
        len--;
        ptr++;
    }
    return b;
}
