/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ashevchu <ashevchu@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/02 14:10:50 by ashevchu      #+#    #+#                 */
/*   Updated: 2023/03/30 19:37:59 by ashevchu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_printf.h"
// #include <stdio.h>

int	print_str(char	*s)
{
	int	i;

	i = 0;
	if (!s)
	{
		ft_putstr_fd_prnt("(null)", 1);
		return (6);
	}
	i = ft_strlen_prnt(s);
	write(1, s, i);
	return (i);
}

int	print_int(int n)
{
	char	*res;
	size_t	len;

	res = ft_itoa_prnt(n);
	len = ft_strlen_prnt(res);
	ft_putstr_fd_prnt(res, 1);
	free(res);
	return (len);
}

int	print_percent(void)
{
	ft_putchar_fd_prnt('%', 1);
	return (1);
}

int	formats(va_list argptr, const char format)
{
	int	res;

	res = 0;
	if (format == 'c')
	{
		ft_putchar_fd_prnt(va_arg(argptr, int), 1);
		res += 1;
	}
	else if (format == 's')
		res += print_str(va_arg(argptr, char *));
	else if (format == 'p')
		res += print_ptr_ox(va_arg(argptr, unsigned long long));
	else if (format == 'd' || format == 'i')
		res += print_int(va_arg(argptr, int));
	else if (format == 'u')
		res += print_unsign(va_arg(argptr, unsigned int));
	else if (format == 'x' || format == 'X')
		res += print_hexi(va_arg(argptr, unsigned int), format);
	else if (format == '%')
		res += print_percent();
	return (res);
}

int	ft_printf(const char *ptr, ...)
{
	int		i;
	va_list	argptr;
	int		res;

	i = 0;
	res = 0;
	va_start (argptr, ptr);
	while (ptr[i])
	{
		if (ptr[i] == '%')
		{
			res += formats(argptr, ptr[i + 1]);
			i++;
		}
		else
		{
			res += 1;
			ft_putchar_fd_prnt(ptr[i], 1);
		}
		if (ptr[i])
			i++;
	}
	va_end (argptr);
	return (res);
}

// int	main(void)
// {
// 	// char	*str = "helloasfsterdhde";
// 	// unsigned int yoyo = 12345;
// 	ft_printf("Hello %");
// 	printf("Hello %");
// }
