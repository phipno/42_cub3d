/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_wrapped.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:52:58 by jwillert          #+#    #+#             */
/*   Updated: 2023/05/21 16:02:40 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>

void	*malloc_wrapped(size_t size_to_alloc, char *file, char *line, int fd)
{
	if (DEBUG_ALLOC == 1)
	{
		ft_putstr_fd(file, fd);
		ft_putstr_fd(" ", fd);
		ft_putstr(line, fd);
		ft_putstr_fd(" ", fd);
		printf("[%zu]", size_to_alloc);
		ft_putstr_fd(" ", fd);
		printf("[%p]\n", )
		return (malloc(size_to_alloc));
	}
	else
	{
		return (malloc(size_to_alloc));
	}
}