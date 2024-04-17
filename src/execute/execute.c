#include "../../include/minishell.h"
#include "../../include/builtins.h"
#include <fcntl.h>

t_cmd_builtin    *builtin_choice(char **parsed) {
    static  const t_cmd_builtin   cmd[] = \
{
    {.name = "cd", .function = ft_cd},
    {.name = "echo", .function = ft_echo},
    {.name = "env", .function = ft_env},
    {.name = "exit", .function = ft_exit},
    {.name = "export", .function = ft_export},
    {.name = "pwd", .function = ft_pwd},
    {.name = "unset", .function = ft_unset},
};
    size_t  i;
    char    **tmp;

    tmp = parsed;
    i = 0;
    // (void)env;
    while (i < sizeof(cmd) / sizeof(t_cmd_builtin)) {
        if (ft_strcmp(*tmp, cmd[i].name) == 0)
            return (cmd[i]);
        ++i;
        tmp++;
    }
    //error handler
    return (NULL);
}

char    *lookup_path(char *cmd) {
    char    **path_split;
    size_t  i;
    char    *test_cmd;


    path_split = null_exit(ft_split(getenv("PATH"), ':'));
    i = 0;
    while (path_split[i]) {
        test_cmd = ft_strjoin3(path_split[i], "/", cmd);
        if (access(test_cmd, X_OK) == 0) {
            break;
        }
        i++;
        free(test_cmd);
    }
    if (path_split[i] == NULL)
        test_cmd = NULL;
    free_double_array(path_split);
    return (test_cmd);
}

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

static  pid_t   execute_single_cmd(char **cmd) {
    char    *path;
    char    **env;
    pid_t   fork_pid;
    
    fork_pid = fork();
    if (fork_pid < 0)
        perror_exit("minishell", EXIT_FAILURE);
    if (fork_pid == 0) {
        path = lookup_path(cmd);
        if (path == NULL)
            perror_exit("no cmd/access", EXIT_FAILURE);
        env = getenviron();
        if (execve(path, cmd, env) == -1)
            perror_exit("execve", EXIT_FAILURE);
    }
    return (fork_pid);
}

int     execute_builtin(char **input, t_cmd_builtin_f builtin_f) {
    char    **env;
    int     ret;

    // env = getenv()
    ret = builtin_f(input, env);
    return(ret);
}

int    single_cmd(char **parsed) {
    pid_t           child_pid;
    t_cmd_builtin   *builtin_func;
    int             backup_fd[2];
    int             ret;

    if (parsed != NULL) {
        builtin_func = builtin_choice(parsed);
        if (builtin_func != NULL) {
            backup_stdinout(backup_fd);
            ret = execute_builtin(parsed, builtin_func);
            restore_stdinout(backup_fd);
            return(ret);
        }
    }
    child_pid = execute_single_cmd(parsed);
    return (wait_children(1, child_pid));
}

void    execute(char **parsed) {
    
    single_cmd(parsed);
}
