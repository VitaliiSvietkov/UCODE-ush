#include "../inc/ush.h"

char *trim (char *s)
{
    int i;
    while (mx_isspace (*s)) s++;   // skip left side white spaces
    for (i = strlen (s) - 1; (mx_isspace (s[i])); i--) ;   // skip right side white spaces
    s[i + 1] = '\0';
    return s;
    //printf ("%s\n", s);
}

int mx_builtin_echo(t_flags_echo *flags, char **data) {
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
        int count = 0;
        for (int i = 0; str[i]; i++) {
            if (str[i] == '"' || str[i] == '\'') {
                str[i] = ' ';
                count++;
            }
        }
        if(count == 2) {
            char *newstr = trim(str);
            mx_printstr(newstr);
        }
        else {
            mx_printerr("Odd number of quotes");
        }
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
        int count = 0;
        for (int i = 0; str[i]; i++) {
            if (str[i] == '"' || str[i] == '\'') {
                str[i] = ' ';
                count++;
            }
        }
        if(count == 2) {
            char *newstr = trim(str);
            mx_printstr(newstr);
        }
        else {
            mx_printerr("Odd number of quotes");
        }
    }
    return 0;
}
