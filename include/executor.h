#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <fcntl.h>

typedef struct  s_childs {
    pid_t   child_pid;
    int     child_count;
    int     pipe_fd[2][2];
}   t_childs;

int     multi_cmd(char **parsed, t_childs *child); 

#endif