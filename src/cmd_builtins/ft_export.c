#include "../../include/minishell.h"

char    **bubble_swap(char **str, size_t pos) {
    char    *temp;
    size_t  i;

    while(str[i] && i < pos)
        i++;
    temp = null_exit(ft_strdup(str[i]));
    if (str[i + 1] != NULL) {
        str[i] = null_exit(ft_strdup(str[i + 1]));
        str[i++] = temp;
        return(str);
    }
    else
        return(NULL);
}



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

static char *ft_str_until_chr(char *str, char chr) {
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

char    **add_equalls(char **env) {
    size_t  i;
    size_t  len;
    char    *after_equalls;

    i = 0;
    len = double_array_len(env);
    while (i < len) {
        after_equalls = ft_strchr(env[i], '=');
        after_equalls++;
        env[i] = null_exit(ft_strjoin3(ft_str_until_chr(env[i], '='), "\"", after_equalls));
        env[i] = null_exit(ft_strjoin(env[i], "\""));
        i++;
    }
    return (env);
}

int    ft_export(char **argv, char **env) {
    char **test;
    size_t  i;
    
    test = null_exit(ft_dstrdup(env));
    test = add_equalls(test);
    test = sort_alph(test);
    if (argv[1] == NULL) {
        i = 0;
        while (test[i] != NULL) {
            ft_putstr_fd("declare -x ", 1);
            ft_putendl_fd(test[i], 1);
            i++;
        }
    }
    else {
        return(1);
    }
    free_double_array(test);
    return(0);
}

