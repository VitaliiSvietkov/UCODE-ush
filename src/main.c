#include "../inc/ush.h"

void handle_ctrl_c(int sig);
void handle_ctrl_z(int sig);

int main(void) {
    char *command = NULL, **parameters = NULL, *line = NULL;

    mx_init_global();

    while (true) {
        signal(SIGINT, handle_ctrl_c);
        signal(SIGTSTP, handle_ctrl_z);
        
        if (isatty(fileno(stdin)))
            mx_type_prompt();
        mx_read_command(&line);

        if (mx_command_substitution(&line) == -1) {
            free(line);
            line = NULL;
            continue;
        }
        char **commands_arr = mx_strsplit(line, ';');
        free(line);
        line = NULL;

        for (int i = 0; commands_arr[i] != NULL; ++i) {
            parameters = mx_strsplit(commands_arr[i], ' ');
            command = mx_strdup(parameters[0]);

            if (mx_execute_builtin(command, parameters, &commands_arr))
                mx_create_process(command, parameters, commands_arr[i]);

            free(command);
            mx_del_strarr(&parameters);

        }
        mx_del_strarr(&commands_arr);
        if (!isatty(fileno(stdin)))
            break;
    }

    mx_free_global();
    return 0;
}

void handle_ctrl_c(int sig) {
    t_jobs *node = jobs;
    while (node->next != NULL)
        node = node->next;
    int pid = node->pid;

    printf("\n");

    if (pid == jobs->pid) {
        mx_free_global();
        exit(130);
    }
    else kill(pid, sig);
}

void handle_ctrl_z(int sig) {
    t_jobs *node = jobs;
    int job_id = 0;
    while (node->next != NULL) {
        if (node->job_id > job_id)
            job_id = node->job_id;
        node = node->next;
    }
    int pid = node->pid;

    if (pid == jobs->pid)
        return;
    
    kill(pid, sig);
    job_id++;
    node->job_id = job_id;
    printf("[%d]  Stopped\t\t\t%s\n", job_id, node->cmd);
    return;
}
