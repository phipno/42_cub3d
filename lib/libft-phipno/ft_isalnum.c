/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:43:26 by pnolte            #+#    #+#             */
/*   Updated: 2022/04/13 11:31:04 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}

// int	main(void)
// {
// 	char	c;
// 	int		result;

// 	c = '5';
// 	result = isalnum(c);
// 	printf("When %c is passed, return value is %d\n", c, result);
// 	printf("When %c is passed, return value is %d\n", c, ft_isalnum(c));
// 	c = 'Q';
// 	result = isalnum(c);
// 	printf("When %c is passed, return value is %d\n", c, result);
// 	printf("When %c is passed, return value is %d\n", c, ft_isalnum(c));
// 	c = 'l';
// 	result = isalnum(c);
// 	printf("When %c is passed, return value is %d\n", c, result);
// 	printf("When %c is passed, return value is %d\n", c, ft_isalnum(c));
// 	c = '+';
// 	result = isalnum(c);
// 	printf("When %c is passed, return value is %d\n", c, ft_isalnum(c));
// 	printf("When %c is passed, return value is %d\n", c, ft_isalnum(c));
// }
