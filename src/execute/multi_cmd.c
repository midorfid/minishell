#include "../../include/minishell.h"
#include "../../include/builtins.h"
#include <fcntl.h>

static void    backup_stdinout(int *backup_fd) {
    backup_fd[STDIN_FILENO] = dup(STDIN_FILENO);
    backup_fd[STDOUT_FILENO] = dup(STDOUT_FILENO);
    if (backup_fd[STDIN_FILENO] < 0 || backup_fd[STDOUT_FILENO] < 0)
        perror_exit("minishell", 1);
}

static void     restore_stdinout(int *backup_fd) {
    if (dup2(backup_fd[STDIN_FILENO], STDIN_FILENO) < 0 || \
        dup2(backup_fd[STDOUT_FILENO], STDOUT_FILENO) < 0)
            perror_exit("minishell", 1);
}

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

int     first_cmd(char **input) {
    pid_t   child;
    int     fd[2];

    child = fork();
    if (child < 0)
        perror_exit("minishell(fork)", EXIT_FAILURE);
    if (child == 0) {

    }
    else {
        if (pipe(fd) < 0)
            perror_exit(minishell(pipe), EXIT_FAILURE);
    }
}

int multi_cmd(char **parsed) {
    size_t  children_c;
    size_t  i;
    pid_t   process_id;

    children_c = child_count(parsed);
    i = 0;
    while (i <= children_c) {
        if (i == 0)
            process_id = first_cmd(parsed);
        else if (i == children_c)
            mid_cmd(parsed, process_id);
        else
            last_cmd(parsed, process_id);
        i++;
    }
}