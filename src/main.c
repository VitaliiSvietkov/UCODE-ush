#include "../inc/ush.h"

//Handler for SIGINT, caused by
//Ctrl-C at keyboard
void handle_sigint(int sig) {
    //printf("HELLO %d\n", sig);
    kill(getpid(), sig);
}

int main(void) {
    envp[0] = getenv("PATH");
    envp[1] = 0;
    char *cmd, *command, **parameters;
    while (true) {
        signal(SIGINT, handle_sigint);
        cmd = (char *)malloc(100);
        command = (char *)malloc(100);
        parameters = (char **)malloc(20);

        mx_type_prompt();
        mx_read_command(command, parameters);
        
        mx_execute_command(cmd, command, parameters);
        
        free(cmd);
        free(command);
        //mx_del_strarr(&parameters);
    }
    return 0;
}

