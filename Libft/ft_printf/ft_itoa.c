/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ashevchu <ashevchu@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 22:47:11 by ashevchu      #+#    #+#                 */
/*   Updated: 2023/03/30 19:39:06 by ashevchu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_printf.h"

static	char	*fill_array(int n, int bool_sign, char	*res, int int_count)
{
	int	null_ter;
	int	not_zero;

	null_ter = int_count;
	int_count = int_count - 1;
	while (int_count >= 0)
	{
		not_zero = n % 10;
		res[int_count] = not_zero + '0';
		n = n / 10;
		int_count--;
	}
	if (bool_sign == 0)
		res[0] = '-';
	res[null_ter] = '\0';
	return (res);
}

static	char	*mem_alloc(int n)
{
	int		m;
	int		int_count;
	int		bool_sign;
	char	*res;

	bool_sign = 1;
	int_count = 0;
	m = n;
	while (m != 0)
	{
		m = m / 10;
		int_count++;
	}
	if (n < 0)
	{
		bool_sign = 0;
		n = n * (-1);
		int_count++;
	}
	if (n == 0 && int_count == 0)
		int_count = 1;
	res = malloc(int_count + 1);
	if (res == NULL)
		return (NULL);
	return (fill_array(n, bool_sign, res, int_count));
}

char	*ft_itoa_prnt(int n)
{
	char	*res;

	if (n == -2147483648)
	{
		res = ft_strdup_prnt("-2147483648");
		if (!res)
			return (NULL);
		return (res);
	}
	return (mem_alloc(n));
}
