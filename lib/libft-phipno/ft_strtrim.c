/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:00:48 by pnolte            #+#    #+#             */
/*   Updated: 2022/04/13 11:33:40 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	size_t			size;
	char			*p;

	if (s1 == NULL)
		return (NULL);
	start = 0;
	while (s1[start] != '\0' && ft_strchr(set, s1[start]))
		start++;
	size = ft_strlen((char *) s1);
	while (size > start && ft_strchr(set, s1[size - 1]))
		size--;
	p = ft_substr(s1, start, (size - start));
	return (p);
}

// int	main(void)
// {
// 	char	s1[] = "mirtYou shall not trim";
// 	char	set[] = "trim";
// 	char	*s2;

// 	s2 = ft_strtrim(s1, set);
// 	printf("%s", s2);
// }
