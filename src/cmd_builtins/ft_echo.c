#include "../../include/minishell.h"
#include <string.h>

int    ft_echo(const char **argv, const char **envp) {
    // handle argv[1] = "echo" - skip
    if(argv[2] != NULL && ft_strcmp(argv[2], "-n") == 0)
        printf("%s", argv[1]);
    else
        printf("%s\n", argv[1]);
    return(0);
}

// void main(int argc, char **argv) {
//     (void)argc;
//     ft_echo(argv);
// }
