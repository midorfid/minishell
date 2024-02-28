#include "../../include/minishell.h"

t_cmd_builtin    builtin_choice(char *argv, char *env) {
    static  const t_cmd_builtin   cmd[] = \
{
    {.name = "cd", .function = ft_cd},
    {.name = "echo", .function = ft_echo},
    {.name = "env", .function = ft_env},
    {.name = "exit", .function = ft_exit},
    {.name = "export", .function = ft_export},
    {.name = "pwd", .function = ft_pwd},
    {.name = "unset", .function = ft_unset},
};
    size_t  i;

    i = 0;
    while (i < cmd/sizeof(t_cmd_builtin)) {
        if (strcmp(argv, cmd[i].name) == 0)
            return (cmd[i]);
        ++i;
    }
    //error handler
    return (NULL);
}

char **parse_input(char **input) {
    
}