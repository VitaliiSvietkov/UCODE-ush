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
        else if (flags->using_U) {
            if (data[2] != NULL) {
                unsetenv(data[2]);
                int i = 1;
                char *s = *environ;
                for (; s; i++) {
                    mx_printstr(s);
                    mx_printchar('\n');
                    s = *(environ + i);
                }
            }
        }
        else if (flags->using_P) {
            if (data[2] != NULL) {
                if (fork() == 0) {
                    char *cmd = NULL;
                    char *envp[] = { getenv("PATH"), 0 };
                    cmd = mx_strnew(256);
                    mx_strcat(cmd, data[2]);
                    execv(cmd, envp);
                    exit(0);
                }
                else {
                    wait(NULL);
                }
            }

        }
        else {
            if (data[1] != NULL) {
                if (data[2] == NULL) {
                    if (fork() == 0) {
                        char *cmd = NULL;
                        char *envp[] = { getenv("PATH"), 0 };
                        cmd = mx_strnew(256);
                        mx_strcpy(cmd, "/bin/");
                        mx_strcat(cmd, data[1]);
                        execv(cmd, envp);
                    }
                    else {
                        wait(NULL);
                    }
                }
                if (data[2] != NULL) {
                    if (fork() == 0) {
                        char *cmd = NULL;
                        char *params[] = {data[2], 0};
                        char *envp[] = { getenv("PATH"), 0 };
                        cmd = mx_strnew(256);
                        mx_strcpy(cmd, "/bin/");
                        mx_strcat(cmd, data[1]);
                        execve(cmd, params, envp);
                    }
                    else {
                        wait(NULL);
                    }
                }
            }
        }
    }
}
