#include "../inc/libmx.h"

char *mx_itoa(int number) {
    if (number == 0) {
        char *res = (char *)malloc(2);
        res[0] = '0';
        res[1] = '\0';
        return res;
    }
    int len = 0;
    int temp = number;
    while (temp > 0) {
        len++;
        temp /= 10;
    }
    char *res;
    int i = 0;
    int j = 0;
    if (number < 0) {
        res = (char *)malloc(len + 2);
        i = 1;
        res[0] = '-';
        number *= -1;
        j = 1;
    }
    else
        res = (char *)malloc(len + 1);
    while (number > 0) {
        res[i] = number % 10 + '0';
        i++;
        number /= 10;
    }
    res[i] = '\0';
    i--;
    for (; j <= i; j++) {
        char tmp = res[j];
        res[j] = res[i];
        res[i] = tmp;
        i--;
    }
    return res;
}
