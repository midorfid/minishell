#include "../include/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char **argv) {
    size_t  i;
    char    *line;
    char    *environment;

    i = 0;
    (void)argc;
    environment = getenv("PATH");
    while(1) {
        line = readline(PROMPT);
        add_history(line);
        builtin_choice(argv[i], environment);
        free(line);
    }
}
