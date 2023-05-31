/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_minimap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:08:24 by jwillert          #+#    #+#             */
/*   Updated: 2023/05/31 17:07:46 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"		// needed for t_minimap, debug_*()
#include "cub3d.h"			// needed for get_rgba()
#include "ft_printf.h"		// needed for ft_printf()

#include <unistd.h>			// needed for STDERR_FILENO
#include <stdio.h>			// needed for printf() (DEBUGGING)

void	debug_print_t_minimap(char *name, t_minimap minimap)
{
	int	fd;

	if (DEBUG)
	{
		fd = DEBUG_FD;
		ft_printf(fd, "__________________\n");
		ft_printf(fd, "%s\n", name);
		debug_print_t_point("minimap.start", minimap.start);
		debug_print_t_point("minimap.end", minimap.start);
		debug_print_t_element("minimap.element", minimap.element);
		ft_printf(fd, "__________________\n");
	}
}

static void	set_array_colours(int32_t *colours)
{
	colours[0] = get_rgba(255, 255, 255, 255);
	colours[1] = get_rgba(0, 0, 0, 255);
	colours[2] = get_rgba(255, 0, 255, 255);
	colours[3] = get_rgba(255, 255, 0, 255);
	colours[4] = get_rgba(0, 255, 0, 255);
}

static void	minimap_init_corner(t_minimap *minimap, size_t max_column, size_t max_line)
{
	size_t	x;
	size_t	y;	
	size_t	size;

	minimap->offset = HEIGHT / 100 * 2;
	size = END_X - START_X;
	x = size / max_column;
	size = END_Y - START_Y;
	y = size / max_line;
	element_set(&minimap->element, x, y);
	point_set(&minimap->start, START_X, START_Y);
	point_set(&minimap->end, END_X + minimap->element.size_x,
		END_Y + minimap->element.size_y);
}

static void	minimap_init_fullscreen(t_minimap *minimap, size_t max_column, size_t max_line)
{
	size_t	x;
	size_t	y;

	x = WIDTH / max_column;
	y = HEIGHT / max_line;
	minimap->offset = HEIGHT / 100 * 10;
	element_set(&minimap->element, x, y);
	point_set(&minimap->start, 0, 0);
	point_set(&minimap->end, WIDTH, HEIGHT);
}

void	minimap_init(t_minimap *minimap, size_t max_column, size_t max_line,
			int mode)
{
	set_array_colours(minimap->colours);
	//@note MODE_OFF?!
	if (mode == MODE_CORNER)
	{
		minimap_init_corner(minimap, max_column, max_line);
	}
	else if (mode == MODE_FULLSCREEN)
	{
		minimap_init_fullscreen(minimap, max_column, max_line);
	}
}
