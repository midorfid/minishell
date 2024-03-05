#include "../include/libft.h"

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
