#include "../../include/minishell.h"

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
