#include "../inc/ush.h"

void mx_cd(char *path) {
    if (chdir(path) < 0) {
        perror("ush");
    }
    else {
        printf("%s\n", getenv("PWD"));
    }
}

