#include "../../include/minishell.h"
#include "../../include/builtins.h"
#include <fcntl.h>
#include "../../include/executor.h"

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
/* execve() TO LOOK UP REGARDING ARGV INPUT, MEANING POINTER TO CONST POINTER*/
int     execute_multi_cmd(char **cmd) {
    t_cmd_builtin   *builtin_f;
    char            *path;
    
    disable_signals();
    last_exit_code = 0;
    if (cmd == NULL || cmd[0] == NULL)
        exit(0);
    builtin_f = builtin_choice(cmd, getenviron());
    if (builtin_f != NULL)
        exit(execute_builtin(*cmd, builtin_f));
    path = lookup_executable(*cmd);
    if (execve(path, cmd, ft_getenviron_value()) < 0)
        perror_exit("minishell", EXIT_FAILURE);
}

void    first_cmd(char **cmd, int **pipe_out) {

}

void     mid_cmd(char **cmd, int pipe_in, int *pipe_out[]) {
    pid_t           fork_id;

    fork_id = fork();
    if (fork_id < 0)
        perror_exit("minishell(fork)", EXIT_FAILURE);
    if (fork_id == 0) {
        if (dup2(pipe_in, STDIN_FILENO) < 0 || \
            dup2(pipe_out[READ], STDOUT_FILENO) < 0)
            perror_exit("minishell(pipe)", EXIT_FAILURE);
        exec_multi_cmd(cmd);
    }
    return(close_pipe_fd());
}

int multi_cmd(char **parsed) {
    size_t  i;
    pid_t   process_id;
    t_childs    childs;

    childs.child_count = child_count(parsed);
    i = 0;
    while (i <= childs.child_count) {
        if (i == 0)
            process_id = first_cmd(parsed, childs.pipe_fd);
        else if (i == childs.child_count)
            last_cmd(parsed, process_id);
        else
            mid_cmd(parsed, process_id);
        while (ft_strcmp(*parsed, "|") != 0)
            parsed++;
        if (ft_strcmp(*parsed, "|") == 0)
            parsed++;
        i++;
    }
}