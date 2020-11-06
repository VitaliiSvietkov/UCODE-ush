#include "../inc/ush.h"

void mx_read_command(char *cmd, char **par) {
    struct winsize max;
    ioctl(0, TIOCGWINSZ, &max);

    char line[max.ws_col];
    int i = 0, j = 0;
    char *array[100], *pch;

    //read one line
    int read = mx_input(line, max.ws_col);
    if (read > max.ws_col - 5)
            exit(1);
    if (read == 0) return;
    pch = strtok(line, " \n");
    
    //parse the line into words
    while (pch != NULL) {
        array[i++] = mx_strdup(pch);
        pch = strtok(NULL, " \n");
    }
    //first word is the command
    mx_strcpy(cmd, array[0]);

    //others are parameters
    for (j = 0; j < i; j++)
        par[j] = array[j];
    par[i] = NULL; //NULL-terminate the par list
}
