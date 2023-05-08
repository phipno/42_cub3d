/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:12:17 by pnolte            #+#    #+#             */
/*   Updated: 2022/04/13 11:33:52 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		c = c - 32;
		return (c);
	}
	else
		return (c);
}

// int	main(void)
// {
// 	char	c;

// 	c = 'm';
// 	printf("\n%c -> %c", c, toupper(c));
// 	printf("\n%c -> %c", c, ft_toupper(c));
// 	c = 'D';
// 	printf("\n%c -> %c", c, toupper(c));
// 	printf("\n%c -> %c", c, ft_toupper(c));
// 	c = '9';
// 	printf("\n%c -> %c", c, toupper(c));
// 	printf("\n%c -> %c", c, ft_toupper(c));
// }
