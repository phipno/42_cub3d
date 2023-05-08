/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:41:57 by pnolte            #+#    #+#             */
/*   Updated: 2022/04/13 11:33:29 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	index;
	size_t	index2;

	index = 0;
	if (needle[index] == 0)
		return ((char *)haystack);
	while (haystack[index] != '\0' && index < len)
	{
		index2 = 0;
		while (haystack[index + index2] == needle[index2]
			&& index + index2 < len)
		{
			if (needle[index2 + 1] == '\0')
				return ((char *)(haystack += index));
			index2++;
		}
		index++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	const char	haystack[] = "see FF your FF return FF now FF";
// 	const char	needle[] = "FF";

// 	printf("LIBE: %s\n", strnstr(haystack, needle, 20));
// 	printf("MINE: %s\n\n", ft_strnstr(haystack, needle, 20));
// 	printf("Here the needle: %s\n", strnstr(haystack, needle, 2));
// 	printf("Here the needle: %s", ft_strnstr(haystack, needle, 2));
// }
