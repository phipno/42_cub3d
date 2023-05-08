/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:06:12 by pnolte            #+#    #+#             */
/*   Updated: 2022/04/13 11:33:17 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen(const char *c)
{
	int	index;

	index = 0;
	while (c[index] != '\0')
		index++;
	return (index);
}

// int	main(void)
// {
// 	char	a[] = "Program";
// 	char	b[] = {'P', 'r', 'o', 'g', 'r', 'a', 'm', '\0'};

// 	printf("Length of string a = %lu \n", strlen(a));
// 	printf("Length of string a = %d \n", ft_strlen(a));
// 	printf("Length of string b = %lu \n", strlen(b));
// 	printf("Length of string b = %d \n", ft_strlen(b));
// }
