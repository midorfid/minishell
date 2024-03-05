#include "../include/minishell.h"
#include <signal.h>

static void    sighandler(int signum) {
    (void)signum;
    ft_putchar_fd('\n', STDERR_FILENO);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    last_exit_code = 1;
}

void    toggle_signals(int bool) {
    if (bool) {
        signal(SIGINT, sighandler);
        signal(SIGQUIT, SIG_IGN);
    }
    else {
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
    }
}
