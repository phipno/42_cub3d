/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_point.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 11:40:43 by jwillert          #+#    #+#             */
/*   Updated: 2023/05/31 11:03:46 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>			// needed for malloc(), free()
#include "minimap.h"	// needed for t_point
#include "ft_printf.h"		// needed for ft_printf()
#include "cub3d.h"			// needed for MACROS
#include <unistd.h>			// needed for STDERR_FILENO

void	debug_print_t_point(char *name, t_point point)
{
	int	fd;

	fd = DEBUG_FD;
	if (DEBUG)
	{
		ft_printf(fd, "______________________\n");
		ft_printf(fd, "t_point: %s\n", name);
		ft_printf(fd, "           %p\n", point);
		ft_printf(fd, "           |x %d|\n", point.x);
		ft_printf(fd, "           |y %d|\n", point.y);
		ft_printf(fd, "______________________\n");
	}
}

void	point_set(t_point *point, int x, int y)
{
	point->x = x;
	point->y = y;
}

t_point	*point_get_new(int x, int y)
{
	t_point	*point_new;

	point_new = malloc (sizeof (t_point));
	if (point_new == NULL)
	{
		return (NULL);
	}
	point_new->x = x;
	point_new->y = y;
	return (point_new);
}
