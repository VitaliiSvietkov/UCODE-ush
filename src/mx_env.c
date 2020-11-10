#include "../inc/ush.h"

void mx_env(char **data) {
    if (data[1] == NULL) { //print all variables
        int i = 1;
        char *s = *environ;
        for (; s; i++) {
            mx_printstr(s);
            mx_printchar('\n');
            s = *(environ + i);
        }
    }
}

