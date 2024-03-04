#include "../include/minishell.h"

void    *null_exit(char *str) {
    if (str == NULL) {
        perror_exit();
    }
    return (str);
}

void    perror_exit(void) {
    perror("minishell");
    exit(EXIT_FAILURE);
}
