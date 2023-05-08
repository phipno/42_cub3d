/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:06:58 by pnolte            #+#    #+#             */
/*   Updated: 2022/04/14 14:06:37 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	counter(long int number)
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

char	*ft_itoa(int n)
{
	char		*str;
	long int	copy;
	int			count;

	copy = n;
	count = counter(copy);
	str = malloc((count + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[count--] = '\0';
	if (copy == 0)
		str = if_zero(str);
	if (copy < 0)
	{
		copy = copy * -1;
		str[0] = '-';
	}
	while (copy > 0)
	{
		str[count] = (copy % 10) + 48;
		copy = copy / 10;
		count--;
	}
	return (str);
}

// int	main(void)
// {
// 	char	*p;

// 	p = ft_itoa(2147483647);
// 	printf("%s\n", p);
// 	p = ft_itoa(-2147483648);
// 	printf("%s\n", p);
// 	p = ft_itoa(0);
// 	printf("%s\n", p);
// 	p = ft_itoa(-12345);
// 	printf("%s\n", p);
// }
