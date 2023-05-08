/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:15:11 by pnolte            #+#    #+#             */
/*   Updated: 2022/06/09 10:55:25 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	hp_hexa_ptr(unsigned long nb)
{
	int			remainder;
	int			count;
	char		*str;

	count = hp_hex_counter(nb) + 2;
	str = malloc(sizeof(char) * (count));
	if (str == NULL)
		return (0);
	str[0] = '0';
	str[1] = 'x';
	if (nb == 0)
		str[2] = '0';
	str[count--] = '\0';
	while (nb != 0)
	{
		remainder = nb % 16;
		if (remainder < 10)
			str[count--] = 48 + remainder;
		else
			str[count--] = ('a' - 10) + remainder;
		nb = nb / 16;
	}
	count = putstring_count(str);
	free(str);
	return (count);
}
