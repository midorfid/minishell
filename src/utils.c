#include "../include/minishell.h"
#include <string.h>
//if found quotes input turns into 2 strings (str + str_quote)
// quotes[0] = '
// quotes[1] = "

// if quotes = empty quotes -> return NULL
// haystack returns quoted str if exists and func returns leftover str
// char	*ft_str_until_chr(const	char **haystack, const	char quotes)
// {
// 	size_t	i;
// 	size_t	j;
// 	char	*leftover;
//     char	*substr;

// 	j = 0;
// 	while (*haystack[j] != '\0')
// 	{
//         if (quotes == &haystack[j])
// 		{
//             leftover = &haystack + j + 1;
//             *haystack = substr;
//             return (leftover);
// 		}
//         *substr = &haystack[j];
//         substr++;
// 		j++;
// 	}
// 	return (NULL);
// }

size_t  double_array_len(char **input) {
    size_t  i;

    i = 0;
    while (input[i]) {
        i++;
    }
    return (i);
}

// char    **insert_str(char **src, char *str) {
//     char    **new_src;
//     size_t  i;

//     i = 0;
//     *new_src = str;
//     *new_src++;
//     while (*src)
//         *new_src = *src;
//     return(new_src);
// }

void    free_double_array(char **src) {
    while(*src) {
        free(*src);
        src++;
    }
    free(src);
}

char    **realloc_double_array(char **src, char *toinsert) {
    char    **res;
    size_t  i;

    i = 0;
    res = malloc(sizeof(char *) * (double_array_len(src) + 2));
    while (*src) {
        *res = strdup(*src);
        src++;
        res++;
    }
    *res = malloc(sizeof(char) * strlen(toinsert) + 1);
    *res = memcpy(*res, toinsert, strlen(toinsert) + 1);
    free_double_array(src);
    return (res);
}

void    main(int argc, char **argv) {
    (void)argc;
    char **res;
    char *str = "it works:)";

    res = realloc_double_array(argv, str);
    while(*res) {
        printf("%s ,", *res);
        *res++;
    }
    free_double_array(res);
}





// char    **find_quotes(const char **str, const char quotes[2]) {
//     size_t  i;
//     size_t  j;
//     char    *leftover;
//     char    *start;
//     char    **new_args;

//     i = 0;
//     j = 0;
//     leftover = NULL
//     new_args = 
//     while (str[i]) {
//         if (leftover) {

//         }
//         // "asd asd fw q"asd 
//         start = ft_strchr(str[i], quotes[0]);
//         if (start == NULL) {
//             // i and j handle
//             new_args[j] = ft_strdup(str[i]);
//             ++i;
//             ++j;    
//         }
//         else {
//             if (start + 1 != NULL && start + 1 == quotes[0]) {
//                 break ;
//             }
//             start++;
//             while (str[i] && ft_str_until_chr(start, '\'') == NULL) {
//                 start = ft_strjoin(start, str[i]);
//                 ++i;
//             }
//         }
//         // else if (str[i] == quotes[1]) {
//     }
//     return (NULL);
// }
