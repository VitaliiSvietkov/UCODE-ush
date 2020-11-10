#pragma once
#define _POSIX_C_SOURCE 200112L //for setenv() and unsetenv()
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include "../libmx/inc/libmx.h"

extern char **environ;
void mx_type_prompt(void);
void mx_read_command(char *cmd, char **par);
int mx_input(char *str, int win_len);

//UNSET block
int mx_unset(const char *name);
int mx_unset_check_param(char **data); //how to unset a func?
//how to check the READ_ONLY for a var name?

//ENV block
void mx_env(char **data);

//PWD block
typedef struct s_flags_pwd
{
    bool using_L;
    bool using_P;//default
}              t_flags_pwd;
void mx_pwd(t_flags_pwd *flags);
void mx_init_flags_pwd(t_flags_pwd *data);//set to default values
void mx_set_flags_pwd(t_flags_pwd *data, char **flags);//set to passing values

//CD block
void mx_cd(char *path);

