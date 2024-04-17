#ifndef BUILTINS_H
#define BUILTINS_H

typedef int (*t_cmd_builtin_f)(char **argv, char **env);

typedef struct s_cmd_builtin
{
    char            *name;
    t_cmd_builtin_f    function;
}   t_cmd_builtin;

int     ft_cd(const char *input);
void    ft_echo(char **argv);
int     ft_exit();
void    ft_pwd();

//to do
void    ft_env();
int    ft_export(char **argv, char **env);
int    ft_unset(char **argv, char **env);

void    print_export(char **toprint);
char    **add_quotes(char **env);
#endif