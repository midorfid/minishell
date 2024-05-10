#include "../include/minishell.h"

int    ft_pwd(const char **argv, const char **envp) {
    char    *abs_path;

    abs_path = getcwd(abs_path, 0);
    printf("%s", abs_path);
    free(abs_path);
}
