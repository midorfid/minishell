#include "../../include/minishell.h"
#include <string.h>

void    ft_echo(char **argv) {
    // handle argv[1] = "echo" - skip
    if(argv[2] != NULL && strcmp(argv[2], "-n") == 0)
        printf("%s", argv[1]);
    else
        printf("%s\n", argv[1]);
}

void main(int argc, char **argv) {
    (void)argc;
    ft_echo(argv);
}
