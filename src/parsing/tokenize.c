#include "../../include/minishell.h"

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
            //check if there is 2 quotes in a row
            if (*(*start + 1) != '\0' && (*(*start) == quotes[SINGLE] && *(*start + 1) == quotes[SINGLE]) \
                || (*(*start) == quotes[DOUBLE] && *(*start + 1) == quotes[DOUBLE])) {
                    leftover = ft_strdup((*start) + 2);
                    if (leftover == NULL)
                        i++;
                    *start = NULL;
                }
            //check quotes in same string, if noone loop line until found or error
            if (*start != NULL && *(*start) == quotes[SINGLE]) {
                (*start)++;
                while (str[i] && leftover == NULL) {
                    leftover = ft_str_until_chr(start, quotes[SINGLE]);
                    if (leftover == NULL) {
                        i++;
                        *start = ft_strjoin(*start, str[i]);
                    }
                    if (str[i] == NULL && leftover != NULL)
                        //error no close quote
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

char    **quotes_check(char **input)  {
    char    quotes[2] = "'\"";
    char    **new_args;

    new_args = find_quotes(input, quotes);
    //free_double_array(input);
    return (new_args);
}
