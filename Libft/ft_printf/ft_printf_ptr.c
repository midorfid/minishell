/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_ptr.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ashevchu <ashevchu@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/11 14:07:26 by ashevchu      #+#    #+#                 */
/*   Updated: 2023/03/30 19:37:27 by ashevchu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_printf.h"

int	len_ptr(unsigned long long p)
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

int	print_ptr(unsigned long long p)
{
	int	print_res;

	print_res = len_ptr(p);
	if (p >= 16)
	{
		print_ptr (p / 16);
		print_ptr (p % 16);
	}
	else
	{
		if (p <= 9)
			ft_putchar_fd_prnt(p + '0', 1);
		else
			ft_putchar_fd_prnt(p - 10 + 'a', 1);
	}
	return (print_res);
}

int	print_ptr_ox(unsigned long long p)
{
	int	print_res;

	print_res = 0;
	print_res += write(1, "0x", 2);
	if (p == 0)
		print_res += write(1, "0", 1);
	else
		print_res += print_ptr(p);
	return (print_res);
}
