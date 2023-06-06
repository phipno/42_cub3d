/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_point.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 11:40:43 by jwillert          #+#    #+#             */
/*   Updated: 2023/06/06 11:00:00 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"		// needed for t_point
#include "cub3d.h"			// needed for MACROS
#include <unistd.h>			// needed for STDERR_FILENO
#include <stdlib.h>			// needed for malloc(), free()

#include <stdio.h>			// needed for dprintf()

void	debug_print_t_point(char *name, t_point point)
{
	int	fd;

	fd = DEBUG_FD;
	if (DEBUG)
	{
		dprintf(fd, "______________________\n");
		dprintf(fd, "t_point: %s\n", name);
		dprintf(fd, "           %p\n", (void *) &point);
		dprintf(fd, "           |x %f|\n", point.x);
		dprintf(fd, "           |y %f|\n", point.y);
		dprintf(fd, "______________________\n");
	}
}

void	point_set(t_point *point, int x, int y)
{
	point->x = x;
	point->y = y;
}

void	point_set_mid(t_point *mid, t_point a, t_point b)
{
	point_set(mid, b.x - a.x, b.y - a.y);
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
