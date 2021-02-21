#include "../inc/ush.h"

//Handler for SIGINT, caused by
//Ctrl-C at keyboard
void handle_ctrl_c(int sig) {
    t_jobs *node = jobs;
    while (node->next != NULL)
        node = node->next;
    int pid = node->pid;
    if (pid == getpid())
        mx_free_global();

    printf("\nMY CTRL-C\n");

    kill(pid, sig);
}

void handle_ctrl_z(int sig) {
    printf(" Pressed CTRL-Z %d", sig);
}

/*
void handle_ctrl_d(int sig) {
    close(stdin);
}
*/

int main(int argc, char *argv[]) {
    if (argv[argc]) {}

    char *command = NULL, **parameters = NULL, *line = NULL;
    char *envp[] = { getenv("PATH"), 0 };

    mx_init_global();

    while (true) {
        signal(SIGINT, handle_ctrl_c);
        signal(SIGTSTP, handle_ctrl_z);

        mx_type_prompt();
        mx_read_command(&line);

        char **commands_arr = mx_strsplit(line, ';');
        free(line);
        line = NULL;

        for (int i = 0; commands_arr[i] != NULL; ++i) {
            parameters = mx_strsplit(commands_arr[i], ' ');
            command = mx_strdup(parameters[0]);

            if (mx_execute_builtin(command, parameters, &commands_arr)) {
                
                int child_pid = fork();
                if (child_pid == 0) {
                    int exec_status = 0;
                    /* char *cmd = mx_strnew(256);
                    mx_strcpy(cmd, "/bin/");
                    mx_strcat(cmd, command); */
                    char *cmd = mx_strjoin("/bin/", command);
                    exec_status = execve(cmd, parameters, envp); //execute command
                    free(cmd);
                    if (exec_status != -1)
                        exit(0);
                    else 
                        exit(1);
                }
                else {
                    t_jobs *new_process = jobs_new_node(child_pid);
                    jobs_push_back(&jobs, &new_process);
                    int child_status = 0;
                    waitpid(child_pid, &child_status, WUNTRACED);
                    t_global.exit_status = WEXITSTATUS(child_status);
                    jobs_remove(&jobs, child_pid);
                    wait(NULL);
                }
                
            }
            //printf("Value of $?: %d\n", t_global.exit_status);
            free(command);
            mx_del_strarr(&parameters);

        }
        mx_del_strarr(&commands_arr);
    }

    mx_free_global();
    return 0;
}
