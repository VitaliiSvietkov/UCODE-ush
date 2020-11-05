#include "../inc/libmx.h"

void *mx_realloc(void *ptr, size_t size) {
    size_t curSize;
    char *newPtr;
    if (ptr == 0)
        return (char *)malloc(size);
    curSize = mx_strlen((char *)ptr);
    if (size <= curSize)
        return ptr;
    newPtr = (char *)malloc(size);
    mx_memcpy(newPtr, ptr, curSize);
    free(ptr);
    return newPtr;
}
