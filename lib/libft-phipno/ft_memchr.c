/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:57:04 by pnolte            #+#    #+#             */
/*   Updated: 2022/04/13 17:17:44 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	a;

	p = (unsigned char *)str;
	a = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (*p == a)
			return ((void *)p);
		i++;
		p++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char s[] = {0, 1, 2 ,3 ,4 ,5};
// 	char *ret;

// 	ret = memchr(s, 2 + 256, 3);
// 	printf("%s", ret);
// 	ret = ft_memchr(s, 2 + 256, 3);
// 	printf("%s", ret);
// }
