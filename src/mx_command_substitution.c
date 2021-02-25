#include "../inc/ush.h"

static char *rep_substr(char *str, char *substr, char *new_str);
//static char *get_exe_command(char *line);

int mx_command_substitution(char **str) {
    char *data = *str;

    char *ptr = mx_strchr(data, '$');
    if (!ptr)
        return 0;
    
    while (ptr != NULL) {
    
        char *tmp_ptr = ptr;

        if (*(ptr + 1) == '(') {
            *ptr = '\0';
            for (; *(tmp_ptr + 1) != '\0';) {
                mx_swap_char(tmp_ptr, tmp_ptr + 1);
                tmp_ptr++;
            }
            *ptr = '\0';
            tmp_ptr = ptr;
            for (; *(tmp_ptr + 1) != '\0';) {
                mx_swap_char(tmp_ptr, tmp_ptr + 1);
                tmp_ptr++;
            }

            tmp_ptr = ptr;
            char *var = mx_strnew(PATH_MAX);
            for (int j = 0; *tmp_ptr != ')' && *tmp_ptr != '\0'; j++) {
                var[j] = *tmp_ptr;
                tmp_ptr++;
            }
            *tmp_ptr = '\0';
            for (; *(tmp_ptr + 1) != '\0';) {
                mx_swap_char(tmp_ptr, tmp_ptr + 1);
                tmp_ptr++;
            }

            /*
            FILE *fp;
            char *strrep = mx_strnew(INT_MAX);
            char *command = get_exe_command(var);
            fp = popen(command, "r");
            if (fp == NULL) {
                mx_printerr("Failed to run command\n");
                return 1;
            }
            fgets(strrep, sizeof(strrep), fp);
            pclose(fp);
            
            data[i] = mx_strrep(data[i], var, strrep);
            free(strrep);
            */

            printf("%s\n", var);
            free(var);
        }
        else if (*(ptr + 1) == '{') {
            *ptr = '\0';
            for (; *(tmp_ptr + 1) != '\0';) {
                mx_swap_char(tmp_ptr, tmp_ptr + 1);
                tmp_ptr++;
            }
            *ptr = '\0';
            tmp_ptr = ptr;
            for (; *(tmp_ptr + 1) != '\0';) {
                mx_swap_char(tmp_ptr, tmp_ptr + 1);
                tmp_ptr++;
            }

            tmp_ptr = ptr;
            char *var = mx_strnew(64);
            for (int j = 0; *tmp_ptr != '}'; j++) {
                if (*tmp_ptr == ' ' || *tmp_ptr == '\0') {
                    mx_printerr("ush: bad substitution\n");
                    free(var);
                    t_global.exit_status = 1;
                    return -1;
                }
                var[j] = *tmp_ptr;
                tmp_ptr++;
            }
            *tmp_ptr = '\0';
            for (; *(tmp_ptr + 1) != '\0';) {
                mx_swap_char(tmp_ptr, tmp_ptr + 1);
                tmp_ptr++;
            }
            char *env = getenv(var);
            if (env == NULL)
                env= "\0";
            *str = mx_strrep(*str, var, env);
            data = *str;
            free(var);
        }
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
                    data = rep_substr(data, "?", mx_itoa(t_global.exit_status));
                return 0;
            }
            char *var = mx_strnew(PATH_MAX);
            for (int j = 0; *tmp_ptr != ' ' && *tmp_ptr != '\0' && *tmp_ptr != '$'; j++) {
                var[j] = *tmp_ptr;
                tmp_ptr++;
            }
            char *env = getenv(var);
            if (env == NULL)
                env = "\0";
            *str = mx_strrep(*str, var, env);
            data = *str;
            free(var);
        }

        ptr = mx_strchr(data, '$');
    }
    return 0;
}

static char *rep_substr(char *str, char *substr, char *new_str) {
    int index = mx_get_substr_index(str, substr);
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

/*
static char *get_exe_command(char *line) {
    if (line) {}
    return line;
}
*/
