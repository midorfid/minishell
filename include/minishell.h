#ifndef MINISHELL_H
#define MINISHELL_H

#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "builtins.h"
#include "../Libft/include/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

#define PROMPT "minishell> "
#define SINGLE  0
#define DOUBLE  1
#define ENABLE  1
#define DISABLE  0
#define READ  0
#define WRITE  1

int     last_exit_code = 0;

t_cmd_builtin       *builtin_choice(char **argv, char **env);
char                **find_quotes(char **str, const char quotes[2]);
size_t              double_array_len(char **input);
void                *free_double_array(char **src);
char                **ft_dstrdup(char **src);

char                **getenviron(void);
void                setenviron(char **new_env);

void                *null_exit(void *str);
void                perror_exit(const char *msg, int error_code);
void                print_error(char *program, char *function, char *error);

void                enable_signals(int bool);
void	            disable_signals(void);

char                **parse_input(char *line);
char                **insert_str(char **src, const char *str, size_t where_to);
char                *ft_str_until_chr(char **str, char chr);
char                **realloc_double_array(char **src, char *toinsert);
size_t              child_count(const char **input);

#endif