#include "../inc/ush.h"

void mx_builtin_echo(t_flags_echo *flags, char **data) {
    if (data[1] != NULL) {
        int i = 1;
        char *str = NULL;
        str = mx_strnew(256);
        while(data[i] != NULL) {
            if(!mx_strcmp(">", data[i]) && data[i+1] != NULL) {
                printf("Write to file");
            }
            else {
                mx_strcat(str, data[i]);
                if(data[i+1] != NULL) {
                    mx_strcat(str, " ");
                }
            }
            i++;
        }
        mx_printstr(str);
        mx_printchar('\n');
    }
    if(flags->using_N) {
        int i = 2;
        char *str = NULL;
        str = mx_strnew(256);
        while(data[i] != NULL) {
            if(!mx_strcmp(">", data[i]) && data[i+1] != NULL) {
                printf("Write to file");
            }
            else {
                mx_strcat(str, data[i]);
                if(data[i+1] != NULL) {
                    mx_strcat(str, " ");
                }
            }
            i++;
        }
        mx_printstr(str);
    }
}
