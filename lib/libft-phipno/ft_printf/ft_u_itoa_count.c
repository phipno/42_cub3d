/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hp_u_itoa_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:16:44 by pnolte            #+#    #+#             */
/*   Updated: 2022/04/21 12:44:17 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*if_zero(char *str)
{
	str[0] = '0';
	return (str);
}

int	hp_u_itoa_count(unsigned int n)
{
	char			*str;
	unsigned int	copy;
	int				count;
	int				countprintf;

	copy = n;
	count = hp_counter(copy);
	str = malloc((count + 1) * sizeof(char));
	if (str == NULL)
		free(str);
	str[count--] = '\0';
	if (copy == 0)
		str = if_zero(str);
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
