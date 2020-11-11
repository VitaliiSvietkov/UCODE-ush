#include "../inc/ush.h"

void mx_env_flags_set(t_flags_env *data, char **param, char **env_command, 
char ***env_util_param, char **altpath) {
    for (int i = 1; param[i] != NULL; i++) {
        if (param[i][0] == '-') {
        
            for (int j = 1; j < mx_strlen(param[i]); j++) {
                if (param[i][j] != 'i' && param[i][j] != 'u'
                && param[i][j] != 'P') {
                    mx_printerr("env: invalid option -- '");
                    mx_printerr(&param[i][j]);
                    mx_printerr("'\nTry 'env --help' for more information.\n");
                    errno = 1;
                    return;
                }
                
                if (param[i][j] == 'i') data->using_I = true;
                if (param[i][j] == 'u') data->using_U = true;
                if (param[i][j] == 'P') {
                    data->using_P = true;
                    *altpath = mx_strdup(param[i + 1]);
                }
            }
            if (altpath != NULL) i++;

        }
        else {
            *env_util_param = param + i;
            *env_command = mx_strdup(*env_util_param[0]);
            break;
        }
    }
}

