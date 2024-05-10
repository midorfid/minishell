#ifndef BUILTINS_H
#define BUILTINS_H

typedef int (*t_cmd_builtin_f)(char **argv, char **env);

typedef struct s_cmd_builtin
{
    char            *name;
    t_cmd_builtin_f    function;
}   t_cmd_builtin;

int     ft_cd(const char **argv, const char **envp);
int    ft_echo(const char **argv, const char **envp);
int     ft_exit(const char **argv, const char **envp);
int    ft_pwd(const char **argv, const char **envp);

//to do
int    ft_env(const char **argv, const char **envp);
int    ft_export(const char **argv, const char **envp);
int    ft_unset(const char **argv, const char **envp);

void    print_export(char **toprint);
char    **add_quotes(char **env);
#endif