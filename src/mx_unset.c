#include "../inc/ush.h"

int mx_unset(const char *name) {
    unsetenv(name);
    return 1;
}

