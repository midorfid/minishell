#include "../include/minishell.h"

void    ft_pwd() {
    char    *abs_path;

    abs_path = getcwd(abs_path, 0);
    printf("%s", abs_path);
    free(abs_path);
}
