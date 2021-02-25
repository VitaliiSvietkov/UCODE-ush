#include "../inc/ush.h"

static char *trim (char *s)
{
    int i;
    while (mx_isspace (*s)) s++;   // skip left side white spaces
    for (i = strlen (s) - 1; (mx_isspace (s[i])); i--) ;   // skip right side white spaces
    s[i + 1] = '\0';
    return s;
    //printf ("%s\n", s);
}

static char *removeSpaces(char *str)
{
    if (*str == '\0') return str;

    char *back = str;
    char *front = str + 1;
    /* In place removal of duplicate spaces*/
    while(*front != '\0')
    {
        if (*front != ' ' || *back != ' ')    // highlight
            *(++back) = *front;
        front++;
    }

    /* After above step add end of string*/
    *(back + 1) = '\0';

    return str;
}

int mx_builtin_echo(t_flags_echo *flags, char **data) {
    if(flags->using_N) {
        bool isWrite = true;
        int i = 2;
        char *str = NULL;
        str = mx_strnew(256);
        while(data[i] != NULL) {
            if(!mx_strcmp(">", data[i]) && data[i+1] != NULL) {
                FILE *file;
                char *path = mx_strdup(getenv("PWD"));
                char *newpath = mx_strcat(path, "/");
                newpath = mx_strcat(newpath, data[i+1]);
                file = fopen(newpath, "w");                
                fprintf(file, "%s", data[i - 1]);
                fclose(file);
                free(path);
                isWrite = false;
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
        bool parants = false;
        for (int i = 0; str[i]; i++) {
            if (str[i] == '"' || str[i] == '\'') {
                for (int j = i; str[j]; j++) {
                    str[j] = str[j + 1];
                }
                count++;
                parants = true;
            }
            else if (str[i] == '\\') {
                if (!parants) {
                    for (int j = i; str[j]; j++) {
                        str[j] = str[j+1];
                    }
                }
            }
        }
        if(count % 2 == 0 || count == 0) {
            if(isWrite) {
                removeSpaces(str);
                char *newstr = trim(str);
                mx_printstr(newstr);
            }
        }
        else {
            mx_printerr("Odd number of quotes.\n");
        }
    }
    else if (data[1] != NULL) {
        bool isWrite = true;
        int i = 1;
        char *str = NULL;
        str = mx_strnew(256);
        while(data[i] != NULL) {
            if(!mx_strcmp(">", data[i]) && data[i+1] != NULL) {
                FILE *file;
                char *path = mx_strdup(getenv("PWD"));
                char *newpath = mx_strcat(path, "/");
                newpath = mx_strcat(newpath, data[i+1]);
                file = fopen(newpath, "w");                
                fprintf(file, "%s", data[i - 1]);
                fclose(file);
                free(path);
                isWrite = false;
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
        bool parants = false;
        for (int i = 0; str[i]; i++) {
            if (str[i] == '"' || str[i] == '\'') {
                for (int j = i; str[j]; j++) {
                    str[j] = str[j + 1];
                }
                count++;
                parants = true;
            }
            else if (str[i] == '\\') {
                if (!parants) {
                    for (int j = i; str[j]; j++) {
                        str[j] = str[j+1];
                    }
                }
            }
        }
        if(count % 2 == 0 || count == 0) { 
            if (isWrite) {
                removeSpaces(str);
                char *newstr = trim(str);
                mx_printstr(newstr);
                mx_printchar('\n');
            }
        }
        else {
            mx_printerr("Odd number of quotes.\n");
        }
    }
    return 0;
}
