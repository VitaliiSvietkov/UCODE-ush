#include "../inc/ush.h"

void mx_builtin_cd(char **params, t_flags_cd *flags) {
    char real_buf[PATH_MAX];
    char *res = NULL;
    char *path = NULL;

    if (params[1][0] == '-' && mx_strlen(params[1]) > 1)
        path = mx_strdup(params[2]);
    else
        path = mx_strdup(params[1]);

    if (path != NULL && flags->using_P) {
        res = realpath(path, real_buf);
        path = mx_strdup(real_buf);
        if (!res)
            free(res);
    }

    int status;
    if (path[0] == '/') {
        if (flags->using_s) {
            char real_buf[PATH_MAX];
            char *res = realpath(path, real_buf);
            if (!res)
                free(res);
            
            if (mx_strcmp(path, real_buf)) {
                mx_printerr("ush: cd: not a directory: ");
                mx_printerr(path);
                mx_printerr("\n");
                if (path != NULL)
                    free(path);
                return;
            }
        }

        status = chdir(path);
        if (status < 0) {
            perror("ush");
            if (path != NULL)
                free(path);
            return;
        }
        status = setenv("OLDPWD", getenv("PWD"), 1);
        status = setenv("PWD", path, 1);
    }
    else {
        // Check if the path is a symlink
        char buf[PATH_MAX];
        ssize_t nbytes = readlink(path, buf, PATH_MAX);
        if (nbytes > 0) {
            if (flags->using_s) {
                char real_buf[PATH_MAX];
                char *res = realpath(path, real_buf);
                if (!res)
                    free(res);
                
                if (mx_strcmp(path, real_buf)) {
                    mx_printerr("ush: cd: not a directory: ");
                    mx_printerr(path);
                    mx_printerr("\n");
                    if (path != NULL)
                        free(path);
                    return;
                }
            }
            status = chdir(path);
            if (status < 0) {
                perror("ush");
                if (path != NULL)
                    free(path);
                return;
            }
            status = setenv("OLDPWD", getenv("PWD"), 1);
            char *tmp_path = mx_strjoin(getenv("OLDPWD"), path);
            status = setenv("PWD", tmp_path, 1);
            free(tmp_path);
            if (path != NULL)
                free(path);
            return;
        }

        res = realpath(path, real_buf);
        if (!res)
            free(res);

        status = chdir(path);
        if (status < 0) {
            perror("ush");
            if (path != NULL)
                free(path);
            return;
        }
        
        status = setenv("OLDPWD", getenv("PWD"), 1);
        status = setenv("PWD", real_buf, 1);
    }

    if (path != NULL)
        free(path);
}
