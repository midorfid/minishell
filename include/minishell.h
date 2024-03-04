#ifndef MINISHELL_H
#define MINISHELL_H

#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../Libft/include/libft.h"
#define PROMPT "minishell> "
#define SINGLE  0
#define DOUBLE  1

typedef int (*t_cmd_builtin_f)(const char **argv, const char **envp);

typedef struct s_cmd_builtin
{
    char            *name;
    t_cmd_builtin_f    function;
}   t_cmd_builtin;

t_cmd_builtin       builtin_choice(char *argv, char *env);
char                **find_quotes(char **str, const char quotes[2]);
size_t              double_array_len(char **input);
void                *free_double_array(char **src);
char                **ft_dstrdup(char **src);

char                **getenviron(void);
void                setenviron(char **new_env);

void                *null_exit(char *str);
void                perror_exit(void);

#endif