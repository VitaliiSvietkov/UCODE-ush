#include "../inc/ush.h"

void mx_buildin_which(t_flags_which *flags, char **data) {
    if (flags->using_A) {
        DIR *d;
        struct dirent *dir;
        int i = 2;
        char *name = NULL;
        char *name_a = NULL;
        while (data[i] != NULL) {
            d = opendir("/bin");
            if (d != NULL) {
                while ((dir = readdir(d)) != NULL) {
                    if (!mx_strcmp(dir->d_name, data[i])) {
                        name = mx_strnew(256);
                        name_a = mx_strnew(256);
                        mx_strcpy(name, "/usr/bin/");
                        mx_strcpy(name_a, "/bin/");
                        mx_strcat(name, data[i]);
                        mx_strcat(name_a, data[i]);
                        mx_printstr(name);
                        mx_printchar('\n');
                        mx_printstr(name_a);
                        mx_printchar('\n');
                    }       
                }
                closedir(d);
            }
            i++;
        }
        
    }
    else if (flags->using_S) {
        DIR *d;
        struct dirent *dir;
        int i = 2;
        char *name = NULL;
        char *name_a = NULL;
        while (data[i] != NULL) {
            d = opendir("/bin");
            if (d != NULL) {
                while ((dir = readdir(d)) != NULL) {
                    if ((!mx_strcmp(dir->d_name, data[i]) && dir->d_type == DT_LNK) || !mx_strcmp(dir->d_name, data[i])) {
                        name = mx_strnew(256);
                        name_a = mx_strnew(256);
                        mx_strcpy(name, "/usr/bin/");
                        mx_strcpy(name_a, "/bin/");
                        mx_strcat(name, data[i]);
                        mx_strcat(name_a, data[i]);
                        mx_printstr(name);
                        mx_printchar('\n');
                        mx_printstr(name_a);
                        mx_printchar('\n');
                    }       
                }
                closedir(d);
            }
            i++;
        }
    }
    
    else if (data[1] != NULL) {
        DIR *d;
        struct dirent *dir;
        int i = 1;
        char *name = NULL;
        while (data[i] != NULL) {
            d = opendir("/bin");
            if (d != NULL) {
                while ((dir = readdir(d)) != NULL) {
                    if (!mx_strcmp(dir->d_name, data[i])) {
                        name = mx_strnew(256);
                        mx_strcpy(name, "/usr/bin/");
                        mx_strcat(name, data[i]);
                        mx_printstr(name);
                        mx_printchar('\n');
                    }       
                }
                closedir(d);
            }
            i++;
        }
    }
}
