/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:50:28 by pnolte            #+#    #+#             */
/*   Updated: 2022/04/13 11:31:23 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

// int	main(void)
// {
// 	char	c;

// 	c = '2';
// 	printf("\nResult when numeric character is passed: %d", ft_isdigit(c));
// 	printf("\nResult when numeric character is passed: %d", isdigit(c));
// 	c = '+';
// 	printf("\nResult when non-numeric character is passed: %d", ft_isdigit(c));
// 	printf("\nResult when non-numeric character is passed: %d", isdigit(c));
// }
