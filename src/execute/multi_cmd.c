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

void    first_cmd(char **cmd, int pipe_out[]) {
    pid_t       fork_id;
    
    fork_id = fork();
    if (fork_id < 0)
        perror_exit("minishell(fork)", EXIT_FAILURE);
    if (fork_id == 0) {
        if (dup2(pipe_out[WRITE], STDOUT_FILENO) < 0)
            perror_exit("minishell", EXIT_FAILURE);
        close(pipe_out[WRITE]);
        close(pipe_out[READ]);
    }
    close(pipe_out[WRITE]);
}

void     mid_cmd(char **cmd, int pipe_in, int pipe_out[]) {
    pid_t           fork_id;

    fork_id = fork();
    if (fork_id < 0)
        perror_exit("minishell(fork)", EXIT_FAILURE);
    if (fork_id == 0) {
        if (dup2(pipe_in, STDIN_FILENO) < 0 || \
            dup2(pipe_out[WRITE], STDOUT_FILENO) < 0)
            perror_exit("minishell(pipe)", EXIT_FAILURE);
        close(pipe_in);
        close(pipe_out[WRITE]);
        close(pipe_out[READ]);
        exec_multi_cmd(cmd);
    }
    close(pipe_in);
    close(pipe_out[WRITE]);
}

int     last_cmd(char **cmd, int pipe_in) {
    pid_t           fork_id;


    fork_id = fork();
    if (fork_id < 0)
        perror_exit("minishell", EXIT_FAILURE);
    if (fork_id == 0) {
        if (dup2(pipe_in, STDIN_FILENO) < 0)
            perror_exit("minishell", EXIT_FAILURE);
        close(pipe_in);
    }
    close(pipe_in);
    return(fork_id);
}

int multi_cmd(char **parsed, t_childs *childs) {
    size_t              i;
    pid_t               process_id;
    static int          flip = 0;

    if (parsed == NULL || parsed[0] == NULL) {
        if (pipe(childs->pipe_fd[flip]) < 0)
            perror_exit("minishell", EXIT_FAILURE);
    }
    childs->child_count = child_count(parsed);
    i = 0;
    while (i <= childs->child_count) {
        if (i == 0)
            first_cmd(parsed, childs->pipe_fd[flip]);
        else if (i == childs->child_count)
            process_id = last_cmd(parsed, childs->pipe_fd[!flip][0]);
        else
            mid_cmd(parsed, childs->pipe_fd[!flip][0], childs->pipe_fd[flip]);
        flip = !flip;
        while (ft_strcmp(*parsed, "|") != 0)
            parsed++;
        if (ft_strcmp(*parsed, "|") == 0)
            parsed++;
        i++;
    }
    return (process_id);
}
