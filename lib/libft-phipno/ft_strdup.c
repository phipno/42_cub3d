/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 10:09:19 by pnolte            #+#    #+#             */
/*   Updated: 2022/04/13 11:32:55 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*d;
	int		size;
	int		index;

	size = 0;
	while (s[size] != '\0')
		size++;
	d = malloc((size + 1) * sizeof(char));
	if (d == NULL)
		return (NULL);
	index = 0;
	while (s[index] != '\0')
	{
		d[index] = s[index];
		index++;
	}
	d[index] = '\0';
	return (d);
}

// int	main(void)
// {
// 	const char	s[] = "Try to dup me!\n";
// 	const char  *d;

// 	d = strdup(s);
// 	puts(d);
// 	d = ft_strdup(s);
// 	puts(d);
// }
