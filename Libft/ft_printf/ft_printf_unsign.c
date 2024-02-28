/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_unsign.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ashevchu <ashevchu@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/11 14:09:00 by ashevchu      #+#    #+#                 */
/*   Updated: 2023/03/30 19:37:38 by ashevchu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_printf.h"
// unsigned itoa
char	*unsign_fill_arr(unsigned int n, char	*res, int int_count)
{
	int				null_ter;
	unsigned int	int_to_a;

	null_ter = int_count;
	int_count = int_count - 1;
	while (int_count >= 0)
	{
		int_to_a = n % 10;
		res[int_count] = int_to_a + '0';
		n = n / 10;
		int_count--;
	}
	res[null_ter] = '\0';
	return (res);
}

char	*unsign_int_mem_alloc(unsigned int n)
{
	unsigned int	m;
	int				int_count;
	char			*res;

	int_count = 0;
	m = n;
	while (m != 0)
	{
		m = m / 10;
		int_count++;
	}
	if (n == 0 && int_count == 0)
		int_count = 1;
	res = malloc(int_count + 1);
	if (res == NULL)
		return (NULL);
	return (unsign_fill_arr(n, res, int_count));
}

int	print_unsign(unsigned int n)
{
	char	*res;
	int		len;

	res = unsign_int_mem_alloc(n);
	len = ft_strlen_prnt(res);
	ft_putstr_fd_prnt(res, 1);
	free(res);
	return (len);
}
