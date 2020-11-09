#include "../inc/ush.h"

int mx_unset(const char *name) {
    return unsetenv(name);
}

