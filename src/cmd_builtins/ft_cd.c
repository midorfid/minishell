#include "../../include/minishell.h"
#include <unistd.h>
#include <string.h>

int ft_cd(const char *input) {
    char    *path;
    char    res[1024];

    path = strchr(input, '$');
    if (path != NULL) {
        char    path_name[128];
        char    *env_name;
        size_t  i;

        i = 0;
        *path++;
        while (*path && *path != ' ' \
            && *path != '\n' && *path != '/')
            path_name[i++] = *path++;
        path_name[i] = '\0';
        env_name = getenv(path_name);
        if (env_name == NULL)
            return (-1);
        ft_strcpy(res, env_name);
    }
    else {
        ft_strcpy(res, input);
    }
    if (chdir(res) == -1) {
        // set errno
        perror("chdir");
        return(-1);
    }
    return(0);
}

// void    main() {
//     //(void)argc;
//     int i = ft_cd("$HOME");
//     if(i == -1) {
//         puts("failed");
//         return ;
//     }
//     char    *abs_path;
//     while(1) {
//         abs_path = getcwd(abs_path, 0);
//         printf("%s\n", abs_path);
//         free(abs_path);
//         sleep(5);
//     }
//     printf("%d\n", i);
// }

