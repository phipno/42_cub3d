/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 09:48:42 by pnolte            #+#    #+#             */
/*   Updated: 2022/04/13 17:28:42 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char			*p;
	unsigned char	a;

	a = (unsigned char)c;
	p = (char *)str;
	while (*p != a)
	{
		if (*p == '\0')
			return (NULL);
		p++;
	}
	return (p);
}

// int	main(void)
// {
// 	const char	str[] = "http://www.tutorialspoint.com";
// 	const char	ch = '.';
// 	const char	c2 = ',';
// 	char		*ret;

// 	ret = strchr(str, ch);
// 	printf("String after (%c) is %s\n", ch, ret);
// 	ret = strchr(str, c2);
// 	printf("String after (%c) is %s\n", c2, ret);
// 	ret = ft_strchr(str, ch);
// 	printf("String after (%c) is %s\n", ch, ret);
// 	ret = ft_strchr(str, c2);
// 	printf("String after (%c) is %s\n", c2, ret);
// }
