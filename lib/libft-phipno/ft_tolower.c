/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:11:29 by pnolte            #+#    #+#             */
/*   Updated: 2022/04/13 11:33:49 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		c = c + 32;
		return (c);
	}
	else
		return (c);
}

// int	main(void)
// {
// 	char	c;

// 	c = 'm';
// 	printf("\n%c -> %c", c, tolower(c));
// 	printf("\n%c -> %c", c, ft_tolower(c));
// 	c = 'D';
// 	printf("\n%c -> %c", c, tolower(c));
// 	printf("\n%c -> %c", c, ft_tolower(c));
// 	c = '9';
// 	printf("\n%c -> %c", c, tolower(c));
// 	printf("\n%c -> %c", c, ft_tolower(c));
// }
