#include "../inc/ush.h"

//Handler for SIGINT, caused by
//Ctrl-C at keyboard
void handle_sigint(int sig) {
    //printf("HELLO %d\n", sig);
    kill(getpid(), sig);
}

int main(void) {
    char *cmd, *command, **parameters;
    char *envp[] = { getenv("PATH"), 0 };
    while (true) {
        signal(SIGINT, handle_sigint);
        cmd = (char *)malloc(100);
        command = (char *)malloc(100);
        parameters = (char **)malloc(20);

        mx_type_prompt();
        mx_read_command(command, parameters);
        
        mx_execute_command(cmd, command, parameters, envp);
        
        free(cmd);
        free(command);
        //mx_del_strarr(&parameters);
    }
    return 0;
}

