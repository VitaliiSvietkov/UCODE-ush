#include "../inc/ush.h"

static char *rep_substr(char *str, char *substr, char *new_str);

void mx_command_substitution(char ***arr) {
    char **data = *arr;

    for (int i = 0; data[i] != NULL; i++) {
        char *ptr = mx_strchr(data[i], '$');
        if (!ptr)
            continue;
        
        char *tmp_ptr = ptr;

        if (*(ptr + 1) == '(') {}
        else if (*(ptr + 1) == '{') {}
        else {
            *ptr = '\0';
            for (; *(tmp_ptr + 1) != '\0';) {
                mx_swap_char(tmp_ptr, tmp_ptr + 1);
                tmp_ptr++;
            }

            tmp_ptr = ptr;
            if (*tmp_ptr == '?' && (*(tmp_ptr + 1) == ' ' || *(tmp_ptr + 1) == '\0')) {
                if (t_global.exit_status < 10)
                    *ptr = *mx_itoa(t_global.exit_status);
                else
                    data[i] = rep_substr(data[i], "?", mx_itoa(t_global.exit_status));
                continue;
            }
            char *var = mx_strnew(64);
            for (int j = 0; *tmp_ptr != ' ' && *tmp_ptr != '\0'; j++) {
                var[j] = *tmp_ptr;
                tmp_ptr++;
            }
            data[i] = mx_strrep(data[i], var, getenv(var));
            free(var);
        }
    }

}

static char *rep_substr(char *str, char *substr, char *new_str) {
    int index = mx_get_char_index(str, *substr);
    if (index == -1)
        return NULL;
    int len = mx_strlen(str + mx_strlen(new_str));
    char *res = mx_strnew(len);
    mx_memcpy(res, str, index);
    mx_memcpy(res + index, new_str, mx_strlen(new_str));
    mx_memcpy(res + index + mx_strlen(new_str), 
        str + index + 1, len - index - 1 - mx_strlen(new_str));
    free(str);
    return res;
}
