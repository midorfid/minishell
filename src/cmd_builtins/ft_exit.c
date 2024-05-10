#include "../../include/builtins.h"
#include "../../include/minishell.h"
#include <stdlib.h>
#include <readline/readline.h>

int ft_exit(const char **argv, const char **envp) {
    (void)envp;
    if (double_array_len(argv) > 2){
        print_error("minishell", "exit", "too many arguments");
        return(1);
    }
    rl_clear_history();
    last_exit_code = 0;
    exit(EXIT_SUCCESS);
}
