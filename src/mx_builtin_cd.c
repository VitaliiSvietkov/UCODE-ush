#include "../inc/ush.h"

void mx_builtin_cd(char *path) {
    int status;
    if (path[0] == '/') {
        status = chdir(path);
        if (status < 0) {
            perror("ush");
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
            status = chdir(path);
            if (status < 0) {
                perror("ush");
                return;
            }
            status = setenv("OLDPWD", getenv("PWD"), 1);
            char *tmp_path = mx_strjoin(getenv("OLDPWD"), path);
            status = setenv("PWD", tmp_path, 1);
            free(tmp_path);
            return;
        }

        char real_buf[PATH_MAX];
        char *res = realpath(path, real_buf);
        if (!res)
            free(res);

        status = chdir(path);
        if (status < 0) {
            perror("ush");
            return;
        }

        /*char *cwd = (char *)malloc(INT_MAX);
        getcwd(cwd, INT_MAX);
        char *ptr = realpath(cwd, NULL);
        if (ptr == NULL)
            printf("Error\n");*/
        
        status = setenv("OLDPWD", getenv("PWD"), 1);
        status = setenv("PWD", real_buf, 1);
        //free(cwd);
    }
}
