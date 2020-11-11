#include "../inc/ush.h"

void mx_env(char *cmd, char **parameters) {
    t_flags_env env_flags;
    char *env_command = NULL;
    char **env_util_param = NULL;
    char *altpath = NULL;
    mx_env_flags_init(&env_flags);
    mx_env_flags_set(&env_flags, parameters, &env_command, &env_util_param, &altpath);  

    if (errno == 1) {
        exit(1);
    }

    if (parameters[1] == NULL) { //print all variables
        int i = 1;
        char *s = *environ;
        for (; s; i++) {
            mx_printstr(s);
            mx_printchar('\n');
            s = *(environ + i);
        }
    }
    else {
        if (env_flags.using_I) {
            char *s = *environ;
            for (int i = 1; s; i++) {
                s = NULL;
                s = *(environ + i);
            }
        }
        
        if (env_flags.using_P) {
            if (altpath) {};
        }
        
        if (env_flags.using_U) {

        }

        mx_execute_command(cmd, env_command, env_util_param);
    }
}

