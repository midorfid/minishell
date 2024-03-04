#include "../include/minishell.h"
#include <string.h>
//if found quotes input turns into 2 strings (str + str_quote)
// quotes[0] = '
// quotes[1] = "

// if quotes = empty quotes -> return NULL
// haystack returns quoted str if exists and func returns leftover str
char	*ft_str_until_chr(char **haystack, const	char quotes)
{
	size_t	i;
	size_t	j;
	char	*leftover;
    char	*substr;

	j = 0;
    i = 0;
    leftover = NULL;
	while (haystack[i][j] != '\0')
	{
        if (quotes == haystack[i][j])
		{
            if (*(*haystack + j + 1) != '\0')
                leftover = ft_strdup(*haystack + j + 1);
            else
                leftover = ft_strdup("NULL");
            substr = malloc(sizeof(char) * j + 1);
            substr = ft_memcpy(substr, *haystack, j);
            substr[j + 1] = '\0';
            *haystack = ft_strdup(substr);
            // free(substr);
            return (leftover);
		}
		j++;
	}
	return (NULL);
}

char    *ft_strjoin3(const char   *start, const char    *mid, const char *end) {
    char    *new;
    size_t  len_start;
    size_t  len_mid;
    size_t  len_end;
    size_t  i;

    len_start = ft_strlen(start);
    len_mid = ft_strlen(mid);
    len_end = ft_strlen(end);
    new = malloc(sizeof(char) * (len_start + len_mid + len_end + 1));
    if(new == NULL)
        return(NULL);
    new = ft_strlcpy(new, start, len_start);
    new = ft_strlcpy(new + len_start, mid, len_mid);
    new = ft_strlcpy(new + len_start + len_mid, end, len_end);
    new[len_start + len_mid + len_end] = '\0';
    return(new);
}

char    **ft_dstrdup(char **src) {
    char    **new;
    size_t  len;
    size_t  i;

    len = double_array_len(src);
    new = malloc(sizeof(char *) * (len + 1));
    if (new == NULL)
        return (NULL);
    while (i < len) {
        new[i] = ft_strdup(src[i]);
        if (new[i] == NULL)
            return (free_double_array(new));
        i++;
    }
    new[i] = NULL;
    return (new);
}

size_t  double_array_len(char **input) {
    size_t  i;

    i = 0;
    while (input[i]) {
        i++;
    }
    return (i);
}

void    *free_double_array(char **src) {
    size_t  i;

    i = 0;
    while(src[i]) {
        free(src[i]);
        i++;
    }
    free(src);
    return(NULL);
}

char    **insert_str(char **src, const char *str, size_t where_to) {
    char    **new_src;
    size_t  i;

    i = 0;
    new_src = malloc(sizeof(char *) * (double_array_len(src) + 2));
    if (new_src == NULL)
        return(NULL);
    while (src[i] != NULL && i < where_to) {
        new_src[i] = strdup(src[i]);
        if (new_src[i] == NULL)
            return((char **)free_double_array(new_src));
        i++;
    }
    new_src[where_to] = strdup(str);
    if (new_src[where_to] == NULL)
        return((char **)free_double_array(new_src));
    while (src[++i] != NULL) {
        new_src[i] = strdup(src[i]);
        if (new_src[i] == NULL)
            return((char **)free_double_array(new_src));
    }
    new_src[i] = NULL;
    return(new_src);
}

char    **realloc_double_array(char **src, char *toinsert) {
    char    **res;
    size_t  i;

    i = 0;
    res = malloc(sizeof(char *) * (double_array_len(src) + 2));
    if (res == NULL)
        return(NULL);
    while (src[i]) {
        res[i] = strdup(src[i]);
        if (res[i] == NULL)
            return(free_double_array(res));
        i++;
    }
    res[i] = strdup(toinsert);
    if (res[i] == NULL)
        return(free_double_array(res));
    res[i + 1] = NULL;
    return (res);
}

// void    main(int argc, char **argv) {
//     (void)argc;
//     char **res;
//     char *str = "it works:)";

//     res = realloc_double_array(argv, str);
//     if (!res)
//         return ;
//     while(*res) {
//         printf("%s ,", *res);
//         *res++;
//     }
//     system("leaks a.out");
//     // free_double_array(res);
// }



char    *ft_strchr_multi(char *str, const char *set) {
    size_t  i;
    size_t  j;

    i = 0;
    while (str[i]) {
        j = 0;
        while (set[j]) {
            if (str[i] == set[j])
                return (str + i);
            j++;
        }
        i++;
    }
    return (NULL);
}

char    **find_quotes(char **str, const char quotes[2]) {
    size_t  i;
    size_t  j;
    char    *leftover;
    char    **start;
    char    **new_args;

    new_args = malloc(sizeof(char *));
    i = 0;
    j = 0;
    start = malloc(sizeof(char *) * 2);
    start[1] = NULL;
    leftover = NULL;
    //NEED TO HANDLE UNCLOSED!!!
    while (str[i]) {
        if (leftover != NULL && ft_strncmp(leftover, "NULL", 4) != 0) {
            str = insert_str(str, leftover, i);
            leftover = NULL;
        }
        if (*start != NULL) {
            new_args = realloc_double_array(new_args, *start);
            j++;
            // start = NULL;
        }
        if (leftover != NULL && ft_strncmp(leftover, "NULL", 4) == 0)
            break;
        *start = ft_strchr_multi(str[i], quotes);
        if (*start == NULL) {
            new_args = realloc_double_array(new_args, str[i]);
            j++;
            ++i;
        }
        else {
            if (*(*start + 1) != '\0' && (*(*start) == quotes[SINGLE] && *(*start + 1) == quotes[SINGLE]) \
                || (*(*start) == quotes[DOUBLE] && *(*start + 1) == quotes[DOUBLE])) {
                    leftover = ft_strdup((*start) + 2);
                    if (leftover == NULL)
                        i++;
                    *start = NULL;
                }
            if (*start != NULL && *(*start) == quotes[SINGLE]) {
                (*start)++;
                while (str[i] && leftover == NULL) {
                    leftover = ft_str_until_chr(start, quotes[SINGLE]);
                    if (leftover == NULL) {
                        i++;
                        *start = ft_strjoin(*start, str[i]);
                    }
                }
            }
            else if (*start != NULL && *(*start) == quotes[DOUBLE]) {
                (*start)++;
                while (str[i] && leftover == NULL) {
                    leftover = ft_str_until_chr(start, quotes[DOUBLE]);
                    if (leftover == NULL) {
                        i++;
                        *start = ft_strjoin(*start, str[i]);
                    }
                }
            }
        }
    }
    new_args[j] = NULL;
    return (new_args);
}

void    main(int argc, char **argv) {
    // (void)argc
    char **res;
    const char quotes[2] = "'\"";

    argv++;
    res = find_quotes(argv, quotes);
    while(*res) {
        printf("%s,", *res);
        *res++;
    }
    system("leaks a.out");
}
