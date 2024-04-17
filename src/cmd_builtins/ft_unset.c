#include "../../include/minishell.h"
#include "../../include/environment.h"

int    ft_unset(char **argv, char **env) {
    char **tmp;
    
    tmp = NULL;
    if (argv[1] != NULL) {
        tmp = add_quotes(&argv[1]);
        ft_unsetenv(*tmp);
    }
    return (0);
}
