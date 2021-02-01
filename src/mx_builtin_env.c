#include "../inc/ush.h"

void mx_builtin_env(t_flags_env *flags, char **data) {
    if (data[1] == NULL) { //print all variables
        int i = 1;
        char *s = *environ;
        for (; s; i++) {
            mx_printstr(s);
            mx_printchar('\n');
            s = *(environ + i);
        }
    }
    else {
        if (flags->using_I) {
            char *s = *environ;
            for (int i = 1; s; i++) {
                s = NULL;
                s = *(environ + i);
            }
        }
    }
}
