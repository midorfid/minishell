/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_hex.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ashevchu <ashevchu@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/10 19:36:35 by ashevchu      #+#    #+#                 */
/*   Updated: 2023/03/30 19:37:19 by ashevchu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_printf.h"

int	len_hex(unsigned int p)
{
	int	len;

	len = 0;
	if (p == 0)
		len++;
	while (p)
	{
		len++;
		p = p / 16;
	}
	return (len);
}

int	print_hexi(unsigned int p, const char format)
{
	int		print_res;

	print_res = len_hex(p);
	if (p >= 16)
	{
		print_hexi (p / 16, format);
		print_hexi (p % 16, format);
	}
	else
	{
		if (p <= 9)
			ft_putchar_fd_prnt(p + '0', 1);
		else if (format == 'x')
			ft_putchar_fd_prnt(p - 10 + 'a', 1);
		else if (format == 'X')
			ft_putchar_fd_prnt(p - 10 + 'A', 1);
	}
	return (print_res);
}
