#include "../../include/environment.h"

//gets env name value
char    *ft_getenv(const char *name) {
    char    **env;
    size_t  len;
    char    *tmp;

    tmp = ft_strjoin(name, "=");
    len = ft_strlen(tmp);
    env = getenviron();
    while (*env) {
        if (ft_strncmp(*env, name, len) == 0) {
            free(tmp);
            return ((*env) + len);
        }
        env++;
    }
    free(tmp);
    return (NULL);
}
