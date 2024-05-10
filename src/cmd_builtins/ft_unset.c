#include "../../include/minishell.h"
#include "../../include/environment.h"

int    ft_unset(const char **argv, const char **envp) {
    char **tmp;
    
    tmp = NULL;
    if (argv[1] != NULL) {
        tmp = add_quotes(&argv[1]);
        ft_unsetenv(*tmp);
    }
    return (0);
}
