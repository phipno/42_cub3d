/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:54:45 by pnolte            #+#    #+#             */
/*   Updated: 2022/04/13 15:55:13 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	size_t		index1;
	size_t		index2;
	char		*p1;
	const char	*p2;

	p1 = s1;
	p2 = s2;
	index1 = 0;
	index2 = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	while (index2 < n)
	{
		p1[index1] = p2[index2];
		index1++;
		index2++;
	}
	return (p1);
}

// int	main(void)
// {
// 	char	str1[] = "swap";
// 	char	str3[] = "lolo";
// 	char	str2[] = "SWAP";

// 	memcpy (str1, str2, sizeof(str2));
// 	puts(str1);
// 	ft_memcpy(str3, str2, sizeof(str2));
// 	puts(str3);
// }
