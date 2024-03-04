#include "../../include/minishell.h"
#include <stdlib.h>

void    ft_setenv(const char *name, const char *value, int overwrite) {
    char    *tmp;
    char    **new_env;
    size_t  env_len;

    if (overwrite != 0)
        return ;
    if (value != NULL)
        tmp = ft_strjoin3(name, "=", value);
    else
        tmp = ft_strdup(name);
    ft_unsetenv(name);
    new_env = null_exit(ft_dstrdup(getenviron()));
    env_len = double_array_len(new_env);
    new_env = ft_realloc(new_env, sizeof(char **) * (env_len + 1), \
            sizeof(char **) * (env_len + 2));
    new_env[env_len] = tmp;
    new_env[env_len + 1] = NULL;
    setenviron(new_env);
}
