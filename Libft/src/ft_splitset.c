#include "../include/libft.h"

static size_t	ft_findchrset(const char *str, const char *set)
{
	int	i;

	i = 0;
	while (str[i] && !ft_strchr(set, str[i]))
		i++;
	return (i);
}

static size_t	ft_split_count(char const *s, const char *set)
{
	size_t	str_cnt;
	size_t	tmp;

	str_cnt = 0;
	while (*s)
	{
		tmp = ft_findchrset(s, set);
		s += tmp;
		if (tmp > 0)
			str_cnt++;
		else
			s++;
	}
	return (str_cnt);
}

static char	**ft_split_build(char const *s, const char *set, char **ret)
{
	size_t	str_cnt;
	size_t	tmp;

	str_cnt = 0;
	while (*s)
	{
		tmp = ft_findchrset(s, set);
		if (tmp > 0)
		{
			ret[str_cnt] = ft_substr(s, 0, tmp);
			if (ret[str_cnt] == NULL)
				return (NULL);
			str_cnt++;
			s += tmp;
		}
		else
			s++;
	}
	ret[str_cnt] = NULL;
	return (ret);
}

void    ft_split_free(char **str){
    size_t i;

    i = 0;
    while(str[i]){
        free(str[i]);
        ++i;
    }
    free(str);
}

char	**ft_splitset(char const *s, const char *set)
{
	char	**ret;

	ret = (char **)malloc((ft_split_count(s, set) + 1) * sizeof(char *));
	if (ret == NULL)
		return (NULL);
	if (ft_split_build(s, set, ret) == NULL)
	{
		ft_split_free(ret);
		return (NULL);
	}
	return (ret);
}
