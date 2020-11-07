#pragma once
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

void mx_type_prompt(void);
void mx_read_command(char *cmd, char **par);
int mx_input(char *str, int win_len);

//PWD block
typedef struct s_flags_pwd
{
    bool using_L;//always true
    bool using_P;
}              t_flags_pwd;
void mx_pwd(t_flags_pwd *flags);
void mx_init_flags_pwd(t_flags_pwd *data);//set to default values
void mx_set_flags_pwd(t_flags_pwd *data, char **flags);//set to passing values

