#include "../inc/ush.h"

static void go_to_parent();
static void go_to_dir(char *dir);

void mx_builtin_cd(char **params, t_flags_cd *flags) {
    char real_buf[PATH_MAX];
    char *res = NULL;
    char *path = NULL;

    char tmp_PWD[PATH_MAX];
    mx_memcpy(tmp_PWD, t_global.PWD, PATH_MAX);

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
        mx_memset(t_global.PWD, '\0', mx_strlen(t_global.PWD));
        t_global.PWD[0] = '/';
    }

    /*
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
    */

    char **arr = mx_strsplit(path, '/');
    for (int i = 0; arr[i] != NULL; i++) {
        if (!mx_strcmp(arr[i], ".."))
            go_to_parent();
        else
            go_to_dir(arr[i]);
    }
    mx_del_strarr(&arr);

    status = chdir(t_global.PWD);
    if (status < 0) {
        mx_printerr("ush: cd: ");
        perror(path);
        mx_memcpy(t_global.PWD, tmp_PWD, PATH_MAX);
    }
    else {
        mx_memcpy(t_global.OLDPWD, tmp_PWD, PATH_MAX);
        status = setenv("OLDPWD", t_global.OLDPWD, 1);
        status = setenv("PWD", t_global.PWD, 1);
    }

    /*
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
    }
    */
    if (path != NULL)
        free(path);
}

static void go_to_parent() {
    char *ptr = strrchr(t_global.PWD, '/');
    if (ptr)
        mx_memset(ptr, '\0', mx_strlen(ptr));
    else
        t_global.PWD[0] = '/';
    
    if (t_global.PWD[0] == '\0')
        t_global.PWD[0] = '/';
}

static void go_to_dir(char *dir) {
    int len = mx_strlen(t_global.PWD);
    if (t_global.PWD[len - 1] != '/')
        t_global.PWD[mx_strlen(t_global.PWD)] = '/';
    mx_memcpy(t_global.PWD + mx_strlen(t_global.PWD), dir, mx_strlen(dir));
}
