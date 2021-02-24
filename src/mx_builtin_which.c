#include "../inc/ush.h"

int mx_builtin_which(t_flags_which *flags, char **data) {
    DIR *d;
    struct dirent *dir;
    bool found = false;
    bool here = true;

    char *builtins[8] = {"cd", "pwd", "env", "which", "echo", "exit", "unset", "fg"};

    if (flags->using_A) {
        int i = 2;
        char *name = NULL;
        char **path_dir = mx_strsplit(getenv("PATH"), ':');

        while (data[i] != NULL) {
            for (int z = 0; z < 8; z++) {
                if (!mx_strcmp(builtins[z], data[i])) {
                    mx_printstr(data[i]);
                    mx_printstr(": shell built-in command\n");
                    found = true;
                    break;
                }
            }
            if (!mx_strcmp(data[i], "export")) {
                mx_printstr("export: shell reserved word\n");
                found = true;
            }

            for (int j = 0; path_dir[j] != NULL; j++) {
                d = opendir(path_dir[j]);
                if (d != NULL) {
                    while ((dir = readdir(d)) != NULL) {
                        if (!mx_strcmp(dir->d_name, data[i])) {
                            name = mx_strnew(256);
                            mx_strcpy(name, path_dir[j]);
                            name = mx_strcat(name, "/");
                            name = mx_strcat(name, data[i]);
                            mx_printstr(name);
                            mx_printchar('\n');
                            free(name);
                            found = true;
                            break;
                        }       
                    }
                    closedir(d);
                }
            }
            if (found == false) {
                here = false;
                mx_printstr(data[i]);
                mx_printstr(" not found\n");
            }
            i++;
        }

        mx_del_strarr(&path_dir);
        if (name == NULL || !here)
            return 1;
        return 0;
    }
    else if (flags->using_S) {
        int i = 2;
        char **path_dir = mx_strsplit(getenv("PATH"), ':');

        while (data[i] != NULL) {
            for (int j = 0; path_dir[j] != NULL; j++) {
                d = opendir(path_dir[j]);
                if (d != NULL) {
                    while ((dir = readdir(d)) != NULL) {
                        if (!mx_strcmp(dir->d_name, data[i])) {
                            mx_del_strarr(&path_dir);
                            found = true;
                            break;
                        }       
                    }
                    closedir(d);
                }
            }
            if (found == false)
                here = false;
            i++;
        }

        mx_del_strarr(&path_dir);
        if (here == false)
            return 1;
        return 0;
    }
    else if (data[1] != NULL) {
        int i = 1;
        char *name = NULL;
        char **path_dir = mx_strsplit(getenv("PATH"), ':');

        while (data[i] != NULL) {
            for (int j = 0; path_dir[j] != NULL; j++) {
                d = opendir(path_dir[j]);
                if (d != NULL) {
                    while ((dir = readdir(d)) != NULL) {
                        if (!mx_strcmp(dir->d_name, data[i])) {
                            name = mx_strnew(256);
                            mx_strcpy(name, path_dir[j]);
                            name = mx_strcat(name, "/");
                            name = mx_strcat(name, data[i]);
                            mx_printstr(name);
                            mx_printchar('\n');
                            free(name);
                            found = true;
                            break;
                        }       
                    }
                    closedir(d);
                }
            }

            if (found == false) {
                here = false;
                mx_printstr(data[i]);
                mx_printstr(" not found\n");
            }
            i++;
        }
        mx_del_strarr(&path_dir);
        if (here)
            return 0;
        return 1;
    }
    else
        return 1;
}
