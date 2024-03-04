#include "../../include/minishell.h"

extern char **environ;

static char **_environ(char **new_env) {
    static char **env = NULL;

    if (new_env != NULL) {
        if (env != NULL)
            env = free_double_array(env);
        env = new_env;
    }
    if (env == NULL)
        env = ft_dstrdup(environ);
    return (env);
}

char    **getenviron(void) {
    return (_environ(NULL));
}

void    setenviron(char **new_env) {
    _environ(new_env);
}
