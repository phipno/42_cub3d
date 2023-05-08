/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:28:08 by pnolte            #+#    #+#             */
/*   Updated: 2022/04/13 11:32:13 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t			index;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	index = 0;
	while (index < n)
	{
		if (s1[index] != s2[index])
			return (s1[index] - s2[index]);
		index++;
	}
	return (0);
}

// int	main(void)
// {
// 	const char	str1[] = "cba";
// 	const char	str2[] = "bba";
// 	const char	str3[] = "aba";
// 	const char	str4[] = "aab";
// 	const char	str5[] = "";
// 	const char	str6[] = " ";

// 	printf("Orignal, Difference: %d\n", memcmp(str1, str2, 1));
// 	printf("42_Func, Difference: %d\n\n", ft_memcmp(str1, str2, 1));
// 	printf("Orignal, Difference: %d\n", memcmp(str3, str4, 3));
// 	printf("42_Func, Difference: %d\n\n", ft_memcmp(str3, str4, 3));
// 	printf("Orignal, Difference: %d\n", memcmp(str5, str6, 3));
// 	printf("42_Func, Difference: %d\n\n", ft_memcmp(str5, str6, 3));
// }
