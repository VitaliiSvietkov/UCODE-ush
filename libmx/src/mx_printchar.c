#include "../inc/libmx.h"

void mx_printchar(char c) {
    char t[] = "0";
    t[0] = c;
    write(1, t, 1);
}
