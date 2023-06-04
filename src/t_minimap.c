/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_minimap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:08:24 by jwillert          #+#    #+#             */
/*   Updated: 2023/06/04 14:42:00 by jwillert         ###   ########          */
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

		debug_print_t_point("minimap.border_start", minimap.border_start);
		debug_print_t_point("minimap.border_end", minimap.border_end);

		debug_print_t_point("minimap.content_start", minimap.content_start);
		debug_print_t_point("minimap.content_end", minimap.content_end);

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
	size_t	size_x;
	size_t	size_y;

	point_set(&minimap->border_start, START_X, START_Y);
	point_set(&minimap->border_end, END_X, END_Y);
	size_x = END_X - START_X;
	size_y = END_Y - START_Y;

	minimap->offset_x = (END_X - START_X) / 100 * 2;
	minimap->offset_y = (END_Y - START_Y) / 100 * 2;
	
	x = size_x / max_column;
	y = size_y / max_line;

	element_set(&minimap->element, x, y);
	point_set(&minimap->content_start, START_X + minimap->offset_x, START_Y + minimap->offset_y);
	point_set(&minimap->content_end, END_X - minimap->offset_x, END_Y - minimap->offset_y);
}

static void	minimap_init_fullscreen(t_minimap *minimap, size_t max_column, size_t max_line)
{
	size_t	x;
	size_t	y;

	minimap->offset_x = WIDTH / 100 * 10;
	minimap->offset_y = HEIGHT / 100 * 10;

	point_set(&minimap->border_start, minimap->offset_x, minimap->offset_y);
	point_set(&minimap->border_end, WIDTH - minimap->offset_x, HEIGHT - minimap->offset_y);

	point_set(&minimap->content_start, 2 * minimap->offset_x, 2 * minimap->offset_y);
	point_set(&minimap->content_end, WIDTH - 2 * minimap->offset_x, HEIGHT - 2 * minimap->offset_y);


	x = (minimap->content_end.x - minimap->content_start.x) / max_column;
	y = (minimap->content_end.y - minimap->content_start.y) / max_line;

	element_set(&minimap->element, x, y);


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
	debug_print_t_minimap("minimap", *minimap);
}
