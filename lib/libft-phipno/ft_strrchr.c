/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 10:27:03 by pnolte            #+#    #+#             */
/*   Updated: 2022/04/13 17:30:11 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char			*p;
	unsigned char	a;

	a = (unsigned char)c;
	p = (char *)str;
	while (*p != '\0')
		p++;
	while (*p != a)
	{
		if (p == &str[0])
		{
			if (*p == a)
				return (p);
			return (NULL);
		}
		p--;
	}
	return (p);
}

// int	main(void)
// {
// 	const char	str[] = "http://www.tutorialspoint.com";
// 	const char	ch = '.';
// 	const char	c2 = ',';
// 	char		*ret;

// 	ret = strrchr(str, ch);
// 	printf("String after (%c) is %s\n", ch, ret);
// 	ret = strrchr(str, c2);
// 	printf("String after (%c) is %s\n", c2, ret);
// 	ret = ft_strrchr(str, ch);
// 	printf("String after (%c) is %s\n", ch, ret);
// 	ret = ft_strrchr(str, c2);
// 	printf("String after (%c) is %s\n", c2, ret);
// }
