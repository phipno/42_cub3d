/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:07:26 by pnolte            #+#    #+#             */
/*   Updated: 2022/04/13 11:33:25 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	index;
	size_t	index2;

	index = 0;
	index2 = 0;
	while ((str1[index] != '\0' || str2[index] != '\0') && index < n)
	{
		if (str1[index] != str2[index])
			return ((unsigned char)str1[index] - (unsigned char)str2[index]);
		index++;
	}
	return (0);
}

// int	main(void)
// {
// 	const char	str1[] = "aba";
// 	const char	str2[] = "bba";
// 	const char	str3[] = "aaa";
// 	const char	str4[] = "aaa";
// 	const char	str5[] = "";
// 	const char	str6[] = " ";

// 	printf("Orignal, Difference: %d\n", strncmp(str1, str2, 1));
// 	printf("42_Func, Difference: %d\n\n", ft_strncmp(str1, str2, 1));
// 	printf("Orignal, Difference: %d\n", strncmp(str3, str4, 3));
// 	printf("42_Func, Difference: %d\n\n", ft_strncmp(str3, str4, 3));
// 	printf("Orignal, Difference: %d\n", strncmp(str5, str6, 3));
// 	printf("42_Func, Difference: %d\n\n", ft_strncmp(str5, str6, 3));
// }
