#include "../include/minishell.h"
#include <unistd.h>

void    multiple_actions(char **argv) {
    int     pipefd[2];
    // char    buff[100];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    __pid_t   pid;
    pid = fork();
    if(pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        close(pipefd[0]);
        write(pipefd[1], argv[0], strlen(argv[0]) + 1);
        close(pipefd[1]);
        exit(EXIT_SUCCESS);
    }
    else {
        
    }
}
