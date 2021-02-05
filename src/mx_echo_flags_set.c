#include "../inc/ush.h"

int mx_echo_flags_set(t_flags_echo *data, char **flags) {
    if (flags[1] != NULL) {
        if (flags[1][0] == '-') {
            for (int i = 1; i < mx_strlen(flags[1]); i++) {

                switch (flags[1][i])
                {
                case 'n':
                    data->using_n = true;
                    break;
                case 'e':
                    data->using_e = true;
                    break;
                case 'E':
                    data->using_E = true;
                    break;
                default:
                    mx_printerr("ush: echo: -");
                    char c = flags[1][i];
                    mx_printerr(&c);
                    mx_printerr(": invalid option\n");
                    mx_printerr("echo: usage: echo [-neE]\n");
                    return 1;
                    break;
                }

            }
        }
    }
    return 0;
}
