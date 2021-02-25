#include "../inc/ush.h"

static char *rep_substr(char *str, char *substr, char *new_str);
static char *get_exe_command(char *line);

int mx_command_substitution(char **str) {
    char *data = *str;

    char *ptr = mx_strchr(data, '`');
    if (ptr) {
        while (ptr != NULL) {
            char *tmp_ptr = ptr;

            *ptr = '\0';
            for (; *(tmp_ptr + 1) != '\0';) {
                mx_swap_char(tmp_ptr, tmp_ptr + 1);
                tmp_ptr++;
            }

            tmp_ptr = ptr;
            char *var = mx_strnew(PATH_MAX);
            int j = 0;
            for (; *tmp_ptr != '`' && *tmp_ptr != '\0'; j++) {
                var[j] = *tmp_ptr;
                tmp_ptr++;
            }
            var[j] = '\0';
            *tmp_ptr = '\0';
            for (; *(tmp_ptr + 1) != '\0';) {
                mx_swap_char(tmp_ptr, tmp_ptr + 1);
                tmp_ptr++;
            }

            char *var2 = mx_strdup(var);

            for (char *tmp = var; *tmp != '\0' && *tmp != ' '; tmp++) {
                char c = *tmp;
                if (c < 97) {
                    c += 32;
                    *tmp = c;
                }
            }

            char **arr = mx_strsplit(var, ';');
            for (int i = 0; arr[i] != NULL; i++) {
                char *command = get_exe_command(var);
                FILE *fp;
                char *strrep = mx_strnew(PATH_MAX);
                fp = popen(command, "r");
                if (fp == NULL) {
                    mx_printerr("Failed to run command\n");
                    return 1;
                }
                char *strrep_ptr = strrep;
                while (fgets(strrep_ptr, PATH_MAX, fp) != NULL) {
                    strrep_ptr = strrep + mx_strlen(strrep);
                    strrep[mx_strlen(strrep) - 1] = ' ';
                }
                strrep[mx_strlen(strrep) - 1] = '\0';
                pclose(fp);
                
                *str = mx_strrep(*str, var2, strrep);
                free(strrep);
                free(command);
            }
            free(var2);
            mx_del_strarr(&arr);

            data = *str;
            free(var);
            ptr = mx_strchr(data, '`');
        }
    }
    
    ptr = strchr(data, '$');
    if (!ptr)
        return 0;

    // Loop for replacing simple $COMMAND
    while (ptr != NULL) {
        if (*(ptr + 1) == '{' || *(ptr + 1) == '(') {
            ptr = strchr(++ptr, '$');
            continue;
        }
        char *tmp_ptr = ptr;

        if (*(ptr + 1) != '(' && *(ptr + 1) != '{') {
            int ptr_len = mx_strlen(ptr) + 2;
            char *str_to_replace = mx_strnew(ptr_len);
            char *str_var = mx_strnew(ptr_len);

            str_to_replace[0] = *tmp_ptr;
            tmp_ptr++;
            for (int i = 1, j = 0; *tmp_ptr != '\0' && *tmp_ptr != ' ' && *tmp_ptr != '$'; i++, j++) {
                str_to_replace[i + 1] = '\0';
                str_var[j + 1] = '\0';

                str_to_replace[i] = *tmp_ptr;
                str_var[j] = *tmp_ptr;
                if (str_var[0] == '?')
                    break;
                tmp_ptr++;
            }

            if (str_var[0] == '?') {
                char *status = mx_itoa(t_global.exit_status);
                *str = rep_substr(*str, str_to_replace, status);
                free(status);
                free(str_to_replace);
                free(str_var);
                ptr = strchr(*str, '$');
                continue;
            }
            
            char *env_val = getenv(str_var);
            char *env = NULL;
            if (env_val == NULL)
                env = mx_strdup("\0");
            else 
                env = mx_strdup(env_val);

            *str = rep_substr(*str, str_to_replace, env);

            free(env);
            free(str_to_replace);
            free(str_var);
        }

        ptr = strchr(*str, '$');
    }

    ptr = strchr(*str, '$');
    if (!ptr)
        return 0;

    // Loop for other simple substitutions like ${COMMAND}
    while (ptr != NULL) {
        if (*(ptr + 1) == '(') {
            ptr = strchr(++ptr, '$');
            continue;
        }
        char *tmp_ptr = ptr;
        if (*(ptr + 1) == '{') {
            int ptr_len = mx_strlen(ptr) + 2;
            char *str_to_replace = mx_strnew(ptr_len);
            char *str_var = mx_strnew(ptr_len);

            str_to_replace[0] = *tmp_ptr;
            str_to_replace[1] = *(tmp_ptr + 1);
            tmp_ptr += 2;
            for (int i = 2, j = 0; *tmp_ptr != '}'; i++, j++) {
                str_to_replace[i + 1] = '\0';
                str_var[j + 1] = '\0';

                str_to_replace[i] = *tmp_ptr;
                if (*tmp_ptr != '}')
                    str_var[j] = *tmp_ptr;
                if (*tmp_ptr == ' ' || *tmp_ptr == '\0') {
                    mx_printerr("ush: bad substitution\n");
                    free(str_to_replace);
                    free(str_var);
                    t_global.exit_status = 1;
                    return -1;
                }
                tmp_ptr++;
                if (*tmp_ptr == '}')
                    str_to_replace[i + 1] = *tmp_ptr;
            }

            char *env_val = getenv(str_var);
            char *env = NULL;
            if (env_val == NULL)
                env = mx_strdup("\0");
            else 
                env = mx_strdup(env_val);

            *str = rep_substr(*str, str_to_replace, env);

            free(env);
            free(str_to_replace);
            free(str_var);
        }
        ptr = strchr(*str, '$');
        if (ptr == tmp_ptr)
            ptr = strchr(++ptr, '$');
    }







    /*
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
            int j = 0;
            for (; *tmp_ptr != ')' && *tmp_ptr != '\0'; j++) {
                var[j] = *tmp_ptr;
                tmp_ptr++;
            }
            var[j] = '\0';
            *tmp_ptr = '\0';
            for (; *(tmp_ptr + 1) != '\0';) {
                mx_swap_char(tmp_ptr, tmp_ptr + 1);
                tmp_ptr++;
            }

            char *var2 = mx_strdup(var);
            for (char *tmp = var; *tmp != '\0' && *tmp != ' '; tmp++) {
                char c = *tmp;
                if (c < 97) {
                    c += 32;
                    *tmp = c;
                }
            }

            char **arr = mx_strsplit(var, ';');
            for (int i = 0; arr[i] != NULL; i++) {
                char *command = get_exe_command(var);
                if (mx_strlen(command) == 0) {
                    mx_printerr("ush: command not found: ");
                    mx_printerr(var2);
                    mx_printerr("\n");
                }
                FILE *fp;
                char *strrep = mx_strnew(PATH_MAX);
                fp = popen(command, "r");
                if (fp == NULL) {
                    mx_printerr("Failed to run command\n");
                    return 1;
                }
                char *strrep_ptr = strrep;
                while (fgets(strrep_ptr, PATH_MAX, fp) != NULL) {
                    strrep_ptr = strrep + mx_strlen(strrep);
                    strrep[mx_strlen(strrep) - 1] = ' ';
                }
                strrep[mx_strlen(strrep) - 1] = '\0';
                pclose(fp);
                
                *str = mx_strrep(*str, var2, strrep);
                free(strrep);
                free(command);
            }
            free(var2);
            mx_del_strarr(&arr);

            data = *str;
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
    */
    return 0;
}

static char *rep_substr(char *str, char *substr, char *new_str) {
    int index = mx_get_substr_index(str, substr);
    if (index == -1)
        return NULL;
    int new_len = mx_strlen(new_str);
    int len = mx_strlen(str) + mx_strlen(new_str);
    char *res = mx_strnew(len);
    mx_memcpy(res, str, index);
    if (new_len > 0)
        mx_memcpy(res + index, new_str, new_len);
    mx_memcpy(res + index + new_len, 
        str + index + mx_strlen(substr), len - index - mx_strlen(substr) - new_len);
    free(str);

    return res;
}

static char *get_exe_command(char *line) {
    char **arr = mx_strsplit(line, ' ');

    char *res = mx_strnew(PATH_MAX);
    char **path_dir = mx_strsplit(getenv("PATH"), ':');

    struct stat sb;
    for (int i = 0; path_dir[i] != NULL; i++) {
        char *cmd = NULL;
        if (arr[0][0] != '/') {
            cmd = mx_strdup(path_dir[i]);
            cmd = mx_strjoin(cmd, "/");
            cmd = mx_strjoin(cmd, arr[0]);
        }
        else 
            cmd = mx_strdup(arr[0]);
        if (lstat(cmd, &sb) != -1) {
            res = mx_strjoin(res, cmd);
            free(cmd);
            res = mx_strjoin(res, line + mx_strlen(arr[0]));
            mx_del_strarr(&path_dir);
            return res;
        }

        if (cmd != NULL) {
            free(cmd);
            cmd = NULL;
        }
    }
    
    return res;
}
