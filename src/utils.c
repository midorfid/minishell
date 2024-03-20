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

char    **insert_str(char **src, const char *str, size_t where_to) {
    char    **new_src;
    size_t  i;

    i = 0;
    new_src = malloc(sizeof(char *) * (double_array_len(src) + 2));
    if (new_src == NULL)
        return(NULL);
    while (src[i] != NULL && i < where_to) {
        new_src[i] = ft_strdup(src[i]);
        if (new_src[i] == NULL)
            return((char **)free_double_array(new_src));
        i++;
    }
    new_src[where_to] = ft_strdup(str);
    if (new_src[where_to] == NULL)
        return((char **)free_double_array(new_src));
    while (src[++i] != NULL) {
        new_src[i] = ft_strdup(src[i]);
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
        res[i] = ft_strdup(src[i]);
        if (res[i] == NULL)
            return(free_double_array(res));
        i++;
    }
    res[i] = ft_strdup(toinsert);
    if (res[i] == NULL)
        return(free_double_array(res));
    res[i + 1] = NULL;
    return (res);
}

// void    main(int argc, char **argv) {
//     // (void)argc
//     char **res;
//     const char quotes[2] = "'\"";

//     argv++;
//     res = find_quotes(argv, quotes);
//     while(*res) {
//         printf("%s,", *res);
//         *res++;
//     }
//     system("leaks a.out");
// }
