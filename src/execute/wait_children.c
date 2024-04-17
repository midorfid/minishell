#include "../../include/minishell.h"
#include "../../include/builtins.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>

static char *og_signals[] = {NULL, \
"Hangup 1\n", \
"\n", \
"Quit 3\n", \
"Illegal instruction 4\n", \
"Trace/BPT trace 5\n", \
"Abort trap 6\n", \
"Bus error 7\n", \
"Floating point exception 8\n", \
"Killed 9\n", \
"User defined signal 1: 10\n", \
"Segmentation fault 11\n", \
"User defined signal 2: 12\n", \
"Broken pipe 13\n", \
"Alarm clock 14\n", \
"Terminated 15\n", \
"Stack fault signal 16\n", \
"Child status changed 17\n", \
"Continue executing 18\n", \
"Stop executing 19\n", \
"Terminal stop 20\n", \
"Background process attempting to read from terminal 22\n", \
"Background process attempting to write to terminal 23\n", \
"Urgent condition on socket 24\n", \
"CPU time limit exceeded 25\n", \
"Virtual timer expired 26\n", \
"Profiling timer expired 27\n", \
"Window size change 28\n", \
"I/O now possible 29\n", \
"Power failure 30\n", \
"Bad system call 31\n", \
};

static int  handle_singal(int signal) {
    if (signal > 0 && signal < 32)
        ft_putstr_fd(og_signals[signal], STDOUT_FILENO);
    return (signal + 128);
}

int     wait_children(size_t    children_count, int last_pid) {
    int     status;
    int     last_status;
    int     pid_ret;
    size_t  i;
    
    i = 0;
    while (i < children_count) {
        pid_ret = waitpid(-1 , &status, 0);
        if (pid_ret < 0)
            perror_exit("minishell", EXIT_FAILURE);
        if (pid_ret == last_pid)
            last_status = status;
        if (WIFEXITED(status) || WIFSIGNALED(status))
            i++;
    }
    if (WIFEXITED(last_status))
        return ((WEXITSTATUS(last_status)));
    else if (WIFSIGNALED(last_status))
        return (handle_signal(WTERMSIG(last_status)));
    return (-1);
}
