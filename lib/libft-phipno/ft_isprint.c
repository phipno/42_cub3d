/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:52:14 by pnolte            #+#    #+#             */
/*   Updated: 2022/04/13 11:31:33 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}

// int	main(void)
// {
// 	int	c;

// 	c = 288;
// 	printf(" %c is passed to isprint(): %d\n", c, isprint(c));
// 	printf(" %c is passed to isprint(): %d\n", c, ft_isprint(c));
// 	c = '\n';
// 	printf(" %c is passed to isprint(): %d\n", c, isprint(c));
// 	printf(" %c is passed to isprint(): %d\n", c, ft_isprint(c));
// }
