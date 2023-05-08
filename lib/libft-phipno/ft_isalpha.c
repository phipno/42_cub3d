/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:47:34 by pnolte            #+#    #+#             */
/*   Updated: 2022/04/13 11:31:16 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

// int	main(void)
// {
// 	char	c;

// 	c = 'A';
// 	printf("\n uppercase: %d", ft_isalpha(c));
// 	printf("\n uppercase: %d", isalpha(c));
// 	c = 'z';
// 	printf("\n lowercase: %d", ft_isalpha(c));
// 	printf("\n lowercase: %d", isalpha(c));
// 	c = '+';
// 	printf("\n non-alphabetic: %d", ft_isalpha(c));
// 	printf("\n non-alphabetic: %d\n", isalpha(c));
// }
