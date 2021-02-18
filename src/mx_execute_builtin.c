#include "../inc/ush.h"

int mx_execute_builtin(char *cmd, char *command, char **params) {
    // EXIT
    if (!mx_strcmp("exit", command)) {
        free(cmd);
        free(command);
        mx_del_strarr(&params);
        //if (params[1] != NULL)
        //    exit(mx_atoi(params[1]));
        //else
            exit(0);
    }
    // UNSET
    else if (!mx_strcmp("unset", command)) {
        if (mx_unset_check_param(params) == 0) {
        
            for (int i = 1; params[i] != NULL; i++) {
                if (mx_builtin_unset(params[i]) < 0) {
                    perror("ush: unset");
                    t_global.exit_status = 1;
                    continue;
                }
            }
            
        }
        return 0;
    }
    // ENV
    else if (!mx_strcmp("env", command)) {
        t_flags_env env_flags;
        mx_env_flags_init(&env_flags);
        if (!mx_env_flags_set(&env_flags, params))
            mx_builtin_env(&env_flags, params);
        return 0;
    }
    // PWD
    else if (!mx_strcmp("pwd", command)) {
        t_flags_pwd pwd_flags;
        mx_pwd_flags_init(&pwd_flags);
        if (!mx_pwd_flags_set(&pwd_flags, params))
            t_global.exit_status = mx_builtin_pwd(&pwd_flags);
        return 0;
    }
    // CD
    else if (!mx_strcmp("cd", command)) {
        t_flags_cd cd_flags;
        mx_cd_flags_init(&cd_flags);
        if (!mx_cd_flags_set(&cd_flags, params))
            t_global.exit_status = mx_builtin_cd(params, &cd_flags);
        return 0;
    }
    //WHICH
    else if (!mx_strcmp("which", command)) {
        t_flags_which which_flags;
        mx_which_flags_init(&which_flags);
        if (!mx_which_flags_set(&which_flags, params))
            mx_buildin_which(&which_flags, params);
        return 0;
    }

    return -1;
}
