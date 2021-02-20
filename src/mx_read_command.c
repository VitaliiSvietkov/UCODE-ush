#include "../inc/ush.h"

void mx_read_command(char **line) {
    struct winsize max;
    ioctl(0, TIOCGWINSZ, &max);

    *line = mx_strnew(max.ws_col);

    //read one line
    int read = mx_input(*line, max.ws_col);
    
    mx_replace_tilda(line);

    if (read > max.ws_col - 5)
            exit(1);
    if (read == 0) return;
}
