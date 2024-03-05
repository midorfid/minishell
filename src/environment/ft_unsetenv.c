#include "../../include/environment.h"

void    ft_unsetenv(const char *name) {
    char    **env;
    char    **env_mod;
    char    *tmp;
    size_t  tmp_len;

    tmp = null_exit(ft_strjoin(name, "="));
    env = getenviron();
    tmp_len = ft_strlen(tmp);
    while (*env) {
        if (ft_strncmp(*env, tmp, tmp_len) == 0 || \
                ft_strcmp(*env, tmp) == 0) {
            free(*env);
            env_mod = env;
            while (*env_mod) {
                *env_mod = *(env_mod + 1);
                env_mod++;
            }
        }
        else
            env++;
    }
    free(tmp);
    setenviron(null_exit(ft_dstrdup(getenviron())));
}
