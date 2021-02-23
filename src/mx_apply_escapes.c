#include "../inc/ush.h"

void mx_apply_escapes(char ***arr) {
    char **data = *arr;

    // Loop SPACE
    for (int i = 0; data[i] != NULL; i++) {
        int len = mx_strlen(data[i]);
        if (data[i][len - 1] == '\\') {
            data[i][len - 1] = ' ';
            data[i] = mx_strjoin(data[i], data[i + 1]);
            free(data[i + 1]);
            data[i + 1] = NULL;
            for (int j = i + 1; data[j + 1] != NULL; j++) {
                char *tmp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = tmp;
            }
            i--;
        }
    }
    //mx_print_strarr(data, "\n");
}
