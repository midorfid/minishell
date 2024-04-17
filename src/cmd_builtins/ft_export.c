#include "../../include/minishell.h"

char    **sort_alph(char **src) {
    size_t  i;
    size_t  j;
    size_t  src_len;
    char    *temp;

    i = 0;
    temp = NULL;
    src_len = double_array_len(src);
    while (i < src_len) {
        j = i + 1;
        while (j < src_len) {
        if (ft_strncmp(src[i], src[j], ft_strlen(src[i])) > 0) {
            temp = src[i];
            src[i] = src[j];
            src[j] = temp;
        }
        j++;
        }
        i++;
    }
    i--;
    free(src[i]);
    src[i] = NULL;
    return (src);
}

static char *ft_str_until_char(char *str, char chr) {
    size_t  i;
    char    *ret;

    i = 0;
    while (str[i])
    {
        if (str[i] == chr) {
            ret = malloc(i + 2);
            ret = ft_memcpy(ret, str, i + 1);
            ret[i + 2] = '\0';
            return(ret);
        }
        i++;
    }
    return (NULL);    
}

char    **add_quotes(char **env) {
    size_t  i;
    size_t  len;
    char    *after_equall;

    i = 0;
    len = double_array_len(env);
    while (i < len) {
        after_equall = ft_strchr(env[i], '=');
        if (after_equall == NULL)
            return(env);
        after_equall++;
        env[i] = null_exit(ft_strjoin3(ft_str_until_char(env[i], '='), "\"", after_equall));
        env[i] = null_exit(ft_strjoin(env[i], "\""));
        i++;
    }
    return (env);
}

void    print_export(char **toprint) {
    size_t  i;

    i = 0;
    while (toprint[i] != NULL) {
        ft_putstr_fd("declare -x ", 1);
        ft_putendl_fd(toprint[i], 1);
        i++;
    }
}

int    ft_export(char **argv, char **env) {
    char    **to_print;
    char    **exported_env;
    
    to_print = null_exit(ft_dstrdup(env));
    if (argv[1] == NULL) {
        to_print = add_quotes(to_print);
        to_print = sort_alph(to_print);
        print_export(to_print);
    }
    else {
        exported_env = null_exit(ft_dstrdup(env));
        exported_env = realloc_double_array(exported_env, argv[1]);
        to_print = sort_alph(to_print);
        to_print = realloc_double_array(to_print, argv[1]);
        to_print = add_quotes(to_print);
        print_export(to_print);
        setenviron(exported_env);
    }
    // free_double_array(to_print);
    return(0);
}

