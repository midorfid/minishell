#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <stdlib.h>
#include "../Libft/include/libft.h"

char            *ft_getenv(const char *name);
void            ft_setenv(const char *name, const char *value, int overwrite);
void            ft_unsetenv(const char *name);
static char     **_environ(char **new_env);
char            **getenviron(void);
void            setenviron(char **new_env);

void            *null_exit(void *str);
#endif