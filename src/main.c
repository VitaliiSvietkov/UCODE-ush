#include "../inc/ush.h"

//Handler for SIGINT, caused by
//Ctrl-C at keyboard
void handle_sigint(int sig) {
    //printf("HELLO %d\n", sig);
    kill(getpid(), sig);
}

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; ++i)
        printf("%s\n", argv[i]);
    char *cmd = NULL, *command = NULL, **parameters = NULL, *line = NULL;
    char *envp[] = { getenv("PATH"), 0 };

    mx_init_global();

    while (true) {
        signal(SIGINT, handle_sigint);
        cmd = mx_strnew(256);
        command = mx_strnew(256);
        parameters = (char **)malloc(20);

        mx_type_prompt();
        mx_read_command(command, parameters, line);
        free(line);
        line = NULL;

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
        //mx_del_strarr(&parameters);
    }

    mx_free_global();
    return 0;
}
