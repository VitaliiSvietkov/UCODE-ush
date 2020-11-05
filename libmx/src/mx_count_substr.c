#include "../inc/libmx.h"

int mx_count_substr(const char *str, const char *sub) {
    if (str == NULL || sub == NULL)
        return -1;
    if (mx_strlen(sub) == 0)
        return 0;
    int counter = 0;
    char *sub_ptr = mx_strstr(str, sub);
    while (sub_ptr != 0) {
        counter++;
        sub_ptr = mx_strstr(sub_ptr + 1, sub);
    }
    return counter;
}
