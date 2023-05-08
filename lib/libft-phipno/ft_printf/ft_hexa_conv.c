/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hp_hexa_conv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:50:35 by pnolte            #+#    #+#             */
/*   Updated: 2022/04/25 12:02:33 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	hp_hex_counter(unsigned long nb)
{
	int	immanuel_cunt;

	immanuel_cunt = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb = nb / 16;
		immanuel_cunt++;
	}
	return (immanuel_cunt);
}

int	hp_hexa_conv(unsigned int nb, char con)
{
	unsigned int	remainder;
	int				count;
	char			*str;

	count = hp_hex_counter(nb);
	str = malloc(sizeof(char) * (count + 1));
	if (str == NULL)
		return (0);
	str[count--] = '\0';
	if (nb == 0)
		str[0] = '0';
	while (nb != 0)
	{
		remainder = nb % 16;
		if (remainder < 10)
			str[count--] = 48 + remainder;
		else if (con == 'x')
			str[count--] = ('a' - 10) + remainder;
		else if (con == 'X')
			str[count--] = ('A' - 10) + remainder;
		nb = nb / 16;
	}
	count = putstring_count(str);
	free(str);
	return (count);
}
