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
        
        //EXIT
        if (!mx_strcmp(command, "exit")) {
            free(cmd);
            free(command);
            //mx_del_strarr(&parameters);
            exit(0);
        }
        
        //UNSET
        if (!mx_strcmp("unset", command)) {
            if (mx_unset_check_param(parameters) == 0) {
            
                for (int i = 1; parameters[i] != NULL; i++) {
                    if (mx_builtin_unset(parameters[i]) < 0) {
                        perror("ush: unset");
                        continue;
                    }
                }
                
            }
        }
        
        if (fork() == 0) {
        
            if (!mx_strcmp("env", command)) {
                t_flags_env env_flags;
                mx_env_flags_init(&env_flags);
                mx_env_flags_set(&env_flags, parameters);
                
                if (errno == 1) {
                    free(cmd);
                    free(command);
                    //mx_del_strarr(&parameters);
                    exit(1);
                }
                
                mx_builtin_env(&env_flags, parameters);
                exit(0);
            }
        
            if (!mx_strcmp("pwd", command)) {
                t_flags_pwd pwd_flags;
                mx_pwd_flags_init(&pwd_flags);
                mx_pwd_flags_set(&pwd_flags, parameters);
                
                if (errno == 1) {
                    free(cmd);
                    free(command);
                    //mx_del_strarr(&parameters);
                    exit(1);
                }
                
                mx_builtin_pwd(&pwd_flags);
                exit(0);
            }
            
            if (!mx_strcmp("cd", command)) {
                mx_builtin_cd(parameters[1]);
                exit(0);
            }
            
            mx_strcpy(cmd, "/bin/");
            mx_strcat(cmd, command);
            execve(cmd, parameters, envp); //execute command
            
            exit(0);
        }
        else {
            wait (NULL); //wait for child
        }
        
        free(cmd);
        free(command);
        //mx_del_strarr(&parameters);
    }
    return 0;
}
