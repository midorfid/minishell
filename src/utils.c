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
	while (haystack[i][j] != '\0')
	{
        printf("char:%c\n", haystack[i][j]);
        if (quotes == haystack[i][j])
		{
            leftover = ft_strdup(*haystack + j + 1);
            substr = malloc(sizeof(char) * j + 1);
            substr = ft_memcpy(substr, *haystack, j);
            substr[j + 1] = '\0';
            printf("subst:%s\n", substr);
            *haystack = ft_strdup(substr);
            printf("hay:%s\n", *haystack);
            free(substr);
            puts("end");
            return (leftover);
		}
		j++;
	}
	return (NULL);
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
    new_src = malloc(sizeof(char *) * double_array_len(src + 2));
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
    while (src[i] != NULL) {
        new_src[i + 1] = strdup(src[i]);
        if (new_src[i + 1] == NULL)
            return((char **)free_double_array(new_src));
        i++;
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





char    **find_quotes(char **str, const char quotes[2]) {
    size_t  i;
    size_t  j;
    char    *leftover;
    char    *start;
    char    **new_args;

    new_args = malloc(sizeof(char *));
    i = 0;
    j = 0;
    start = NULL;
    leftover = NULL;
    while (str[i]) {
        if (leftover != NULL) {
            str = insert_str(str, leftover, i);
            leftover = NULL;
        }
        if (start != NULL) {
            new_args = realloc_double_array(new_args, start);
            printf("start:%s\n", start);
            j++;
            // start = NULL;
        }
        start = ft_strchr(str[i], quotes[0]);
        if (start == NULL) {
            puts("hello");
            new_args = realloc_double_array(new_args, str[i]);
            j++;
            ++i;
        }
        else {
            if (*start + 1 != '\0' && *start + 1 == quotes[0]) {
                i++;
                start = NULL;
                break ;
            }
            start++;
            printf("ogstart:%s\n", start);
            while (str[i] && leftover == NULL) {
                puts("loop");
                leftover = ft_str_until_chr(&start, quotes[0]);
                if (leftover == NULL) {
                    i++;
                    start = ft_strjoin(start, str[i]);
                }
            }
        }
        // else if (str[i] == quotes[1]) {
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
