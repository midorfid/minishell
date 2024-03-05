#include "../include/minishell.h"

t_cmd_builtin    *builtin_choice(char **parsed, char *env) {
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
    char    **tmp;

    tmp = parsed;
    i = 0;
    (void)env;
    while (i < sizeof(cmd) / sizeof(t_cmd_builtin)) {
        if (ft_strcmp(*tmp, cmd[i].name) == 0)
            return (cmd[i]);
        ++i;
        tmp++;
    }
    //error handler
    return (NULL);
}

char    **find_quotes(char **str, const char quotes[2]) {
    size_t  i;
    size_t  j;
    char    *leftover;
    char    **start;
    char    **new_args;

    new_args = malloc(sizeof(char *));
    i = 0;
    j = 0;
    start = malloc(sizeof(char *) * 2);
    start[1] = NULL;
    leftover = NULL;
    //NEED TO HANDLE UNCLOSED!!!
    while (str[i]) {
        if (leftover != NULL && ft_strncmp(leftover, "NULL", 4) != 0) {
            str = insert_str(str, leftover, i);
            leftover = NULL;
        }
        if (*start != NULL) {
            new_args = realloc_double_array(new_args, *start);
            j++;
            // start = NULL;
        }
        if (leftover != NULL && ft_strncmp(leftover, "NULL", 4) == 0)
            break;
        *start = ft_strchr_multi(str[i], quotes);
        if (*start == NULL) {
            new_args = realloc_double_array(new_args, str[i]);
            j++;
            ++i;
        }
        else {
            if (*(*start + 1) != '\0' && (*(*start) == quotes[SINGLE] && *(*start + 1) == quotes[SINGLE]) \
                || (*(*start) == quotes[DOUBLE] && *(*start + 1) == quotes[DOUBLE])) {
                    leftover = ft_strdup((*start) + 2);
                    if (leftover == NULL)
                        i++;
                    *start = NULL;
                }
            if (*start != NULL && *(*start) == quotes[SINGLE]) {
                (*start)++;
                while (str[i] && leftover == NULL) {
                    leftover = ft_str_until_chr(start, quotes[SINGLE]);
                    if (leftover == NULL) {
                        i++;
                        *start = ft_strjoin(*start, str[i]);
                    }
                }
            }
            else if (*start != NULL && *(*start) == quotes[DOUBLE]) {
                (*start)++;
                while (str[i] && leftover == NULL) {
                    leftover = ft_str_until_chr(start, quotes[DOUBLE]);
                    if (leftover == NULL) {
                        i++;
                        *start = ft_strjoin(*start, str[i]);
                    }
                }
            }
        }
    }
    new_args[j] = NULL;
    return (new_args);
}

char    **quotes_check(char **input)  {
    char    quotes[2] = "'\"";
    char    **new_args;

    new_args = find_quotes(input, quotes);
    //free_double_array(input);
    return (new_args);
}

char    **parse_input(char *line) {
    char    **split;
    char    **no_quotes;
    t_cmd_builtin   *cmd;

    split = ft_split(line, ' ');
    no_quotes = quotes_check(split);
    free_double_array(split);
    cmd = builtin_choice(no_quotes, NULL);
    if (cmd != NULL) {
        while (ft_strcmp(cmd->name, *no_quotes) != 0)
            no_quotes++;
        no_quotes++;
        cmd->function(no_quotes);
    }
    if (cmd == NULL) {
        rl_clear_history();
        exit(EXIT_FAILURE);
    }
    return(NULL);
}
