#include "../../include/minishell.h"
// #include "../Libft/get_next_line/include/get_next_line.h"
#include <fcntl.h>
// < //
char    **redirect_input(const char **input) {
    int     fd;
    char    *buff[1024];
    char    *temp;
    char    **res;
    size_t  i;

    if (*(input) == NULL) {
        perror("redirect no input");
        exit(EXIT_FAILURE);
    }
    fd = open(*(input), O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    temp = get_next_line(fd);
    while (temp) {
        buff[i] = ft_strdup(temp);
        temp = get_next_line(fd);
        i++;
    }
    buff[i] = NULL;
    close(fd);
    res = ft_dstrdup(buff);
    return (res);
}
// << // copies /n as well not sure if it should // FIX GNL COPING \n AT THE END
char    **redirect_input_untilchr(const char *input) {
    int     fd;
    char    *buff[1024];
    char    **res;
    char    *temp;
    size_t  i;

    // if (input == NULL) {
    //     perror("redirect no input");
    //     exit(EXIT_FAILURE);
    // }
    // fd = open(input, O_RDONLY);
    // if (fd == -1) {
    //     perror("open");
    //     exit(EXIT_FAILURE);
    // }
    temp = get_next_line(STDIN_FILENO);
    while (temp) {
        if (ft_strcmp(temp, input) == 10)
            break;
        buff[i] = ft_strdup(temp);
        temp = get_next_line(STDIN_FILENO);
        i++;
    }
    buff[i] = NULL;
    close(fd);
    res = ft_dstrdup(buff);
    return (res);
}

void    main(int argc, char **argv) {
    char **buff;

    buff = redirect_input_untilchr(argv[2]);
    while(*(buff) != NULL) {
        printf("%s", *(buff));
        buff++;
    }
}
