#include "../inc/ush.h"

int main(void) {
    //t_commands commands;
    char *cmd, *command, **parameters;
    char *envp[] = { (char *)"PATH=/bin", 0 };
    while (true) {
        cmd = (char *)malloc(100);
        command = (char *)malloc(100);
        parameters = (char **)malloc(20);

        mx_type_prompt();
        mx_read_command(command, parameters);

        if (fork()) {
            wait (NULL);
        }
        else {
            mx_strcpy(cmd, "/bin/");
            mx_strcat(cmd, command);
            execve(cmd, parameters, envp); //execute command
        }
        //EXIT
        if (!mx_strcmp(command, "exit")) {
            exit(0);
        }
        
        free(cmd);
        free(command);
        mx_del_strarr(&parameters);
        //mx_commands_init(&commands);
        //mx_commands_set(&commands, mx_strsplit(input, ' '));

    }
    return 0;
}

