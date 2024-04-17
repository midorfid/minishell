#include "../include/minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

void    open_pipe(char **input) {
    pid_t   pid; 
    int     fd[2];

    if (pipe(fd) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }
    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        //child
    }
    else {
        //parent
    }
}
