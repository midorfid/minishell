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

void    enable_signals(int bool) {
    if (bool) {
        signal(SIGINT, sighandler);
        signal(SIGQUIT, SIG_IGN);
    }
    else {
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
    }
}

void	disable_signals(void)
{
	rl_catch_signals = 1;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}