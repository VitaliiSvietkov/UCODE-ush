#include "../inc/ush.h"

void mx_set_flags_pwd(t_flags_pwd *data, char **flags) {
    if (flags[1] != NULL) {
        if (flags[1][0] == '-') {
            for (int i = 1; i < mx_strlen(flags[1]); i++) {
                if (flags[1][i] == 'L') {
		    data->using_L = true;
		    continue;
		}
		if (flags[1][i] != 'L' && flags[1][i] != 'P') {
                    mx_printerr("ush: pwd: -");
                    char c = flags[1][i];
                    mx_printerr(&c);
                    mx_printerr(": invalid option\n");
                    mx_printerr("pwd: usage: pwd [-LP]\n");
                    errno = 1;
                    break;
                }
            }
        }
    }
}

