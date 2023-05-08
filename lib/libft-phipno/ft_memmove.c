/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:56:08 by pnolte            #+#    #+#             */
/*   Updated: 2022/04/13 11:32:23 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*dest1;
	const char	*src1;
	size_t		index;

	dest1 = dest;
	src1 = src;
	index = 1;
	if (dest1 > src1)
	{
		while (index <= n)
		{
			dest1[n - index] = src1[n - index];
			index++;
		}
	}
	else
		ft_memcpy(dest1, src1, n);
	return (dest1);
}

// int	main(void)
// {
// 	char	dest1[] = "memove is easy";
// 	char	dest2[] = "";
// 	char	src1[] = "memmo3";
// 	char	src2[] = "";
// 	char	overlap[] = "123456789";

// 	ft_memmove(overlap, overlap +3, 6);
// 	memmove(dest1, src1, 4);
// 	puts(overlap);
// 	ft_memmove(dest2, src2, 4);
// 	puts(dest2);
// }
