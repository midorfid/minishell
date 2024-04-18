#include "../../include/minishell.h"
#include <fcntl.h>

size_t  child_count(const char **input) {
    int     i;
    char    **input_p;
    size_t  children;

    input_p = input;
    i = 0;
    children = 0;
    while (input_p[i]) {
        if (ft_strcmp(input_p[i], ">") == 0 || ft_strcmp(input_p[i], "<") == 0 \
            || ft_strcmp(input_p[i], ">>") || ft_strcmp(input_p[i], "<<")) {
            if (input_p[i + 1] == NULL || open(input[i + 1], O_RDONLY) < 0)
                perror_exit("syntax error near unexpected token: redirection", EXIT_FAILURE);
            }
        else if (ft_strcmp(input_p[i], "|")) {
            children++;
            if (input[i + 1] == NULL)
                perror_exit("syntax error near unexpected token: |", EXIT_FAILURE);
            else if (i > 0 && input[i - 1] == NULL)
                perror_exit("syntax error near unexpected token: |", EXIT_FAILURE);
        }
        i++;
    }
    retrun(children)
}
