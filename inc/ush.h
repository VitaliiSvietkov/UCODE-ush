#pragma once

#define _POSIX_C_SOURCE 200112L //for setenv() and unsetenv()
#define _XOPEN_SOURCE 500 // for realpath() on Linux
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>

#include <pwd.h>
#include <time.h>
#include <grp.h>
#include <sys/acl.h>
#include <sys/xattr.h>
#include <sys/param.h>
#include <termios.h>
#include <term.h>
#include <curses.h>
//#include <malloc/malloc.h>
#include <termios.h>

#include "../libmx/inc/libmx.h"

#define TILDA "~\0"


extern char **environ;
void mx_init_global(void);
void mx_free_global(void);
char *mx_strrep(char *str, char *substr, char *replace);
void mx_replace_tilda(char **str);

struct s_global
{
    char *PWD;
    char *OLDPWD;
    char *HOME;
    int exit_status;
}      t_global;

void mx_type_prompt(void);
int mx_input(char *str, int win_len);
void mx_read_command(char *cmd, char **par, char *line);
int mx_execute_builtin(char *cmd, char *command, char **params);

// CD block
//===============================================================
typedef struct s_flags_cd
{
    bool using_s;
    bool using_P;
}              t_flags_cd;

int mx_builtin_cd(char **params, t_flags_cd *flags);
void mx_cd_flags_init(t_flags_cd *data);
int mx_cd_flags_set(t_flags_cd *data, char **flags);
//===============================================================


// ENV block
//===============================================================
typedef struct s_flags_env
{
    bool using_I;
    bool using_U;
    bool using_P;
}              t_flags_env;

void mx_builtin_env(t_flags_env *flags, char **data);
void mx_env_flags_init(t_flags_env *data);
int mx_env_flags_set(t_flags_env *data, char **param);
//===============================================================


// PWD block
//===============================================================
typedef struct s_flags_pwd
{
    bool using_L;
    bool using_P; //default
}              t_flags_pwd;

int mx_builtin_pwd(t_flags_pwd *flags);
void mx_pwd_flags_init(t_flags_pwd *data);
int mx_pwd_flags_set(t_flags_pwd *data, char **flags);
//===============================================================


int mx_builtin_unset(const char *name);
int mx_unset_check_param(char **data);
