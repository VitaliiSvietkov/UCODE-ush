#include "../inc/ush.h"

//Handler for SIGINT, caused by
//Ctrl-C at keyboard
void handle_sigint(int sig) {
    //printf("HELLO %d\n", sig);
    kill(getpid(), sig);
}

int main(void) {
    char *cmd = NULL, *command = NULL, **parameters = NULL;
    char *envp[] = { getenv("PATH"), 0 };
    while (true) {
        signal(SIGINT, handle_sigint);
        cmd = mx_strnew(256);
        command = mx_strnew(256);
        parameters = (char **)malloc(20);

        mx_type_prompt();
        mx_read_command(command, parameters);

        if (mx_execute_builtin(cmd, command, parameters)) {
        
            if (fork() == 0) {        
                mx_strcpy(cmd, "/bin/");
                mx_strcat(cmd, command);
                execve(cmd, parameters, envp); //execute command
                exit(0);
            }
            else {
                wait (NULL); //wait for child
            }
            
        }
        
        free(cmd);
        free(command);
        mx_del_strarr(&parameters);
    }
    return 0;
}
