#include "../inc/ush.h"

void mx_init_global(void) {
    t_global.PWD = mx_strnew(PATH_MAX);
    memset(t_global.PWD, '\0', PATH_MAX);
    t_global.PWD = mx_strcpy(t_global.PWD, getenv("PWD"));

    t_global.OLDPWD = mx_strnew(PATH_MAX);
    memset(t_global.OLDPWD, '\0', PATH_MAX);
    char *system_var = getenv("OLDPWD");
    if (system_var != NULL)
        t_global.OLDPWD = mx_strcpy(t_global.OLDPWD, system_var);

    t_global.HOME = mx_strnew(PATH_MAX);
    memset(t_global.HOME, '\0', PATH_MAX);
    system_var = getenv("HOME");
    if (system_var != NULL)
        t_global.HOME = mx_strcpy(t_global.HOME, system_var);

    jobs = jobs_new_node(getpid(), "ush");
}

void mx_free_global(void) {
    free(t_global.PWD);
    free(t_global.OLDPWD);
    free(t_global.HOME);
    jobs_clear(&jobs);
}
