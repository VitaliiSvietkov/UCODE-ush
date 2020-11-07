#pragma once
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "../libmx/inc/libmx.h"

void mx_type_prompt(void);
void mx_read_command(char *cmd, char **par);
int mx_input(char *str, int win_len);

