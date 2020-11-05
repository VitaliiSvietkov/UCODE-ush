#include "../inc/ush.h"

int main(void) {
    struct winsize max;
    ioctl(0, TIOCGWINSZ, &max);
    
    char *shell = "u$h> ";
    t_commands commands;
    while (true) {
        mx_printstr(shell);
        char *input = (char *)malloc(max.ws_col);
        int read = mx_input(input, max.ws_col);
        if (read > max.ws_col - 5)
            break;
        
        //EXIT
        if (!mx_strcmp(input, "exit")) {
            free(input);
            exit(0);
        }
        
        mx_commands_init(&commands);
        mx_commands_set(&commands, mx_strsplit(input, ' '));

    }
    return 0;
}

