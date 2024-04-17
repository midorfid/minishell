#include "../include/minishell.h"
#include "../include/environment.h"

// char *line_signals(const char *prompt) {
//     char    *line;

//     toggle_signals(ENABLE);
//     line = readline(prompt);
//     toggle_signals(DISABLE);
//     if (line == NULL) {
//         rl_clear_history();
//         ft_putendl_fd("exit", STDERR_FILENO);
//         exit(last_exit_code);
//     }
//     if (*line == '\0') {
//         free(line);
//         return (NULL);
//     }
//     add_history(line);
//     return(line);
// }

// //shl_lvl
// void    init_shell(char **argv) {
//     char    *shlvl;
//     int     shell_count;
//     char    *new_shlvl;

//     ft_setenv("SHELL", argv[0], 1);
//     shlvl = ft_getenv("SHLVL");
//     if (!shlvl) {
//         ft_setenv("SHLVL", "1", 1);
//         return ;
//     }
//     shell_count = ft_atoi(shlvl);
//     shell_count++;
//     new_shlvl = null_exit(ft_itoa(shell_count));
//     ft_setenv("SHLVL", new_shlvl, 1);
//     free(new_shlvl);
// }

//handle signals

int main(int argc, char **argv) {
    // char    *line;

    (void)argc;
    // rl_catch_signals = 0;
    // rl_outstream = stderr;
    // init_shell(argv);
    // while(1) {
    //     line = line_signals(PROMPT);
    //     parse_input(line);
    //     free(line);
    // }
    ft_export(argv, getenviron());
    ft_unset(argv, getenviron());
    print_export(getenviron());
    return(0);
}
