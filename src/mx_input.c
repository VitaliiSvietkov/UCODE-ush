#include "../inc/ush.h"

int mx_input(char *str, int win_len) {
    int res = read(0, str, win_len);
    str[res - 1] = '\0';
    return res - 1;
}
