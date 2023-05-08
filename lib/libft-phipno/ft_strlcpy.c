/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:04:39 by pnolte            #+#    #+#             */
/*   Updated: 2022/04/13 11:33:13 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	index;
	size_t	src_leng;

	index = 0;
	src_leng = 0;
	while (src[src_leng] != '\0')
		src_leng++;
	if (dstsize == 0)
		return (src_leng);
	while (src[index] != '\0' && index < dstsize - 1)
	{
		dst[index] = src[index];
		index++;
	}
	dst[index] = '\0';
	return (src_leng);
}

// int	main(void)
// {
// 	char	dst1[] = "You wont succed >D";
// 	char	src2[] = "Succeded you have ;D";
// 	char	dst3[] = "You wont succed >D";
// 	char	src4[] = "Succeded you have ;D";
// 	char	dst5[] = "You wont succed >D";
// 	char	src6[] = "Succeded you have ;D";
// 	char	dst7[] = "You wont succed >D";
// 	char	src8[] = "Succeded you have ;D";

// 	strlcpy(dst1, src2, 19);
// 	puts(dst1);
// 	strlcpy(dst3, src4, 1);
// 	puts(dst3);
// 	ft_strlcpy(dst5, src6, 19);
// 	puts(dst5);
// 	ft_strlcpy(dst7, src8, 1);
// 	puts(dst7);
// }
