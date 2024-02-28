/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ashevchu <ashevchu@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 22:40:07 by ashevchu      #+#    #+#                 */
/*   Updated: 2023/03/30 19:38:11 by ashevchu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_printf.h"

size_t	ft_strlen_prnt(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr_fd_prnt(char *s, int fd)
{
	size_t	str_len;

	str_len = ft_strlen_prnt(s);
	write(fd, s, str_len);
}

void	ft_putchar_fd_prnt(char c, int fd)
{
	write (fd, &c, 1);
}

char	*ft_strdup_prnt(const char *s1)
{
	char	*ptr;
	int		i;

	i = 0;
	while (s1[i])
		i++;
	ptr = malloc(i + 1);
	if (ptr == NULL)
		return (ptr);
	while (i >= 0)
	{
		ptr[i] = s1[i];
		i--;
	}
	return (ptr);
}
