#include "../../include/environment.h"

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

char **ft_getenviron_value() {
    char    **ep;
    char    **env;
    char    **shift;

    env = null_exit(ft_dstrdup(getenviron()));
    ep = env;
    while(*ep) {
        if (ft_strchr_multi(*ep, "=") == NULL) {
            free(*ep);
            shift = ep;
            while (*shift) {
                *shift = *(shift + 1);
                shift++;
            }
        }
        else
            ep++;
    }
    return (env);
}
