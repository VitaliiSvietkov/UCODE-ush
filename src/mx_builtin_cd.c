#include "../inc/ush.h"

void mx_builtin_cd(char *path) {
    if (chdir(path) < 0) {
        perror("ush");
    }
}
