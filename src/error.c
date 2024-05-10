#include "../include/minishell.h"

void    *null_exit(void *str) {
    if (str == NULL) {
        perror_exit("minishell", EXIT_FAILURE);
    }
    return (str);
}

void    perror_exit(const char *msg, int error_code) {
    perror(msg);
    exit(error_code);
}

void    print_error(char *program, char *function, char *error) {
    ft_putstr_fd(program, STDERR_FILENO);
    ft_putstr_fd(": ", STDERR_FILENO);
    ft_putstr_fd(function, STDERR_FILENO);
    ft_putstr_fd(": ", STDERR_FILENO);
    ft_putendl_fd(error, STDERR_FILENO);
}
