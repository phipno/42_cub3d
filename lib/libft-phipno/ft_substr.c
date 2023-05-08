/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:17:45 by pnolte            #+#    #+#             */
/*   Updated: 2022/04/14 14:41:52 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static unsigned int	new_length(unsigned int s_len, unsigned int s, size_t len)
{
	unsigned int	new_len;

	if (s >= len)
		new_len = 0;
	if (s >= s_len)
		new_len = 0;
	else if (s_len >= len)
		new_len = len;
	else if (len > s_len)
		new_len = s_len;
	return (new_len);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t			i;
	unsigned int	s_len;
	char			*d;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	len = new_length(s_len, start, len);
	d = malloc((len + 1) * sizeof(char));
	if (d == NULL)
		return (NULL);
	i = 0;
	while (s[start] != '\0' && i < len)
	{
		d[i] = s[start];
		i++;
		start++;
	}
	d[len] = '\0';
	return (d);
}

// int main()
// {
// 	char	s[] = "tripouille";
// 	int		start =  100;
// 	int		len = 1;
// 	char	*dest;

// 	dest = ft_substr(s, start, len);
// 	printf("%s", dest);
// }
