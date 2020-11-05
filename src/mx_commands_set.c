#include "../inc/ush.h"

void mx_commands_set(t_commands *commands, char **arr) {
    if (!mx_strcmp(arr[0], "pwd")) commands->using_pwd = true;
    else {
        mx_printerr("ush: command not found: ");
        mx_printerr(arr[0]);
        mx_printerr("\n");
    }
    mx_del_strarr(&arr);
}

