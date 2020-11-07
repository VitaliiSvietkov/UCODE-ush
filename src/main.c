#include "../inc/ush.h"

int main(void) {
    char *cmd, *command, **parameters;
    char *envp[] = { (char *)"PATH=/bin", 0 };
    while (true) {
        cmd = (char *)malloc(100);
        command = (char *)malloc(100);
        parameters = (char **)malloc(20);

        mx_type_prompt();
        mx_read_command(command, parameters);

        if (fork() == 0) {
            mx_strcpy(cmd, "/bin/");
            mx_strcat(cmd, command);
            execve(cmd, parameters, envp); //execute command
            exit(0);
        }
        else {
            wait (NULL); //wait for child
        }
        
        //EXIT
        if (!mx_strcmp(command, "exit")) {
            free(cmd);
            free(command);
            mx_del_strarr(&parameters);
            exit(0);
        }
        
        free(cmd);
        free(command);
        mx_del_strarr(&parameters);
    }
    return 0;
}

