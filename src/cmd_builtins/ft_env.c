#include "../../include/minishell.h"
#include "../../include/environment.h"

int ft_env(char **argv, char **env) {
    size_t  i;

    if (double_array_len(argv) != 1) {
        print_error("minishell", "env", "too many arguments");
        return (1);
    }
    while (env[i]) {
        ft_putstr_fd(env[i], STDOUT_FILENO);
        i++;
    }
    return (0);
}
