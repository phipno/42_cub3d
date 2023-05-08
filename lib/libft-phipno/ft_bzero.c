/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:22:26 by pnolte            #+#    #+#             */
/*   Updated: 2022/04/13 11:30:31 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*p;

	p = s;
	while (n != 0)
	{
		n--;
		p[n] = '\0';
	}
}

// int	main(void)
// {
// 	char	str[25] = "Trz to replace me";
// 	char	str2[25] = "Trz to replace me again";

// 	printf ("%s\n", str);
// 	bzero (str, 2);
// 	printf ("%s\n", str);
// 	ft_bzero (str2, 2);
// 	puts (str2);
// }
