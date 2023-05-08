/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hp_itoa_count.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 09:34:18 by pnolte            #+#    #+#             */
/*   Updated: 2022/06/01 11:18:54 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	hp_counter(long int number)
{
	int		count;

	count = 0;
	if (number == 0)
		count++;
	if (number < 0)
	{
		number = number * -1;
		count++;
	}
	while (number > 0)
	{
		number = number / 10;
		count++;
	}
	return (count);
}

static char	*if_zero(char *str)
{
	str[0] = '0';
	return (str);
}

long int	if_negativ(int long copy, char *str)
{
	copy = copy * -1;
	str[0] = '-';
	return (copy);
}

int	hp_itoa_count(int n)
{
	char		*str;
	long int	copy;
	int			count;
	int			countprintf;

	copy = n;
	count = hp_counter(copy);
	str = malloc((count + 1) * sizeof(char));
	if (str == NULL)
		free(str);
	str[count--] = '\0';
	if (copy == 0)
		str = if_zero(str);
	if (copy < 0)
		copy = if_negativ(copy, str);
	while (copy > 0)
	{
		str[count] = (copy % 10) + 48;
		copy = copy / 10;
		count--;
	}
	countprintf = putstring_count(str);
	free(str);
	return (countprintf);
}
