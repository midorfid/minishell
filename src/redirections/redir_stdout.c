#include "../../include/minishell.h"
#include <fcntl.h>
// >> //
void    redirect_output_append(const char *filename) {
    int fd;

    fd = open(filename, O_CREAT | O_WRONLY | O_RDONLY | O_APPEND, 0644);
    if (fd == -1) {
        perror("redirect output. file open error");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("redirect output. dup2 failed");
        exit(EXIT_FAILURE);
    }
    close(fd);
}
// > //
void    redirect_output(const char *filename) {
    int fd;

    fd = open(filename, O_CREAT | O_WRONLY | O_RDONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("redirect output. file open error");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("redirect output. dup2 failed");
        exit(EXIT_FAILURE);
    }
    close(fd);
}


void    main(int argc, char **argv) {
    redirect_output_append(argv[1]);
    printf(" nice)))");
}
