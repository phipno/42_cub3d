/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:57:32 by pnolte            #+#    #+#             */
/*   Updated: 2022/04/13 11:32:26 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	char	*p;

	p = str;
	while (n != 0)
	{
		n--;
		p[n] = c;
	}
	return (p);
}

// int	main(void)
// {
// 	char	str[] = "plz replace me";
// 	char	str2[] = "plz replace me";

// 	puts(str);
// 	memset(str, '$', 7);
// 	puts(str);
// 	ft_memset(str2, '$', 7);
// 	puts(str2);
// 	return (0);
// }
