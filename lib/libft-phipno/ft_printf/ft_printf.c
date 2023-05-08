/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 12:47:06 by pnolte            #+#    #+#             */
/*   Updated: 2022/06/01 11:47:58 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	putchar_count(char c)
{
	int	count;

	write(1, &c, 1);
	count = 1;
	return (count);
}

int	putstring_count(char *str)
{
	int	count;

	if (str == NULL)
	{
		putstring_count("(null)");
		return (6);
	}
	count = 0;
	while (str[count] != '\0')
	{
		write(1, &str[count], 1);
		count++;
	}
	return (count);
}

static int	con_check(char con, va_list args)
{
	int	count;

	count = 0;
	if (con == 'c')
		count += putchar_count(va_arg(args, int));
	if (con == 's')
		count += putstring_count(va_arg(args, char *));
	if (con == 'p')
		count += hp_hexa_ptr(va_arg(args, unsigned long));
	if (con == 'd')
		count += hp_itoa_count(va_arg(args, int));
	if (con == 'i')
		count += hp_itoa_count(va_arg(args, int));
	if (con == 'u')
		count += hp_u_itoa_count(va_arg(args, unsigned int));
	if (con == 'x')
		count += hp_hexa_conv(va_arg(args, int), con);
	if (con == 'X')
		count += hp_hexa_conv(va_arg(args, int), con);
	if (con == '%')
		count += putchar_count('%');
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(args, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			count += con_check(str[i + 1], args);
			i++;
		}
		else
			count += putchar_count(str[i]);
		i++;
	}
	va_end(args);
	return (count);
}
