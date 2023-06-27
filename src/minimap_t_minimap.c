/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_t_minimap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:08:24 by jwillert          #+#    #+#             */
/*   Updated: 2023/06/27 13:32:10 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"		// needed for t_minimap, debug_*()
#include "cub3d.h"			// needed for cub_get_rgba()
#include <unistd.h>			// needed for STDERR_FILENO
#include <stdio.h>			// needed for dprintf()

void	debug_print_t_minimap(char *name, t_minimap minimap)
{
	int	fd;

	if (DEBUG)
	{
		fd = DEBUG_FD;
		dprintf(fd, "__________________\n");
		dprintf(fd, "%s\n", name);
		debug_print_t_point("minimap.border_start", minimap.border_start);
		debug_print_t_point("minimap.border_end", minimap.border_end);
		debug_print_t_point("minimap.content_start", minimap.content_start);
		debug_print_t_point("minimap.content_end", minimap.content_end);
		debug_print_t_element("minimap.element", minimap.element);
		dprintf(fd, "minimap.offset_x [%f]\n", minimap.offset_x);
		dprintf(fd, "minimap.offset_y [%f]\n", minimap.offset_y);
		dprintf(fd, "minimap.size_x [%f]\n", minimap.size_x);
		dprintf(fd, "minimap.size_y [%f]\n", minimap.size_y);
		dprintf(fd, "__________________\n");
		dprintf(fd, "\n");
	}
}

static void	set_array_colours(int32_t *colours)
{
	colours[0] = cub_get_rgba(255, 255, 255, 255);
	colours[1] = cub_get_rgba(0, 0, 0, 255);
	colours[2] = cub_get_rgba(255, 0, 255, 255);
	colours[3] = cub_get_rgba(255, 255, 0, 255);
	colours[4] = cub_get_rgba(0, 255, 0, 255);
}

static void	minimap_init_corner(t_minimap *minimap, double max_column,
		double max_line)
{
	double	size_x;
	double	size_y;
	double	scale;

	scale = (double) cub_get_bigger_sizet(max_column, max_line);
	minimap->offset_x = (WIDTH / 3 - START_X) / 100 * 2;
	minimap->offset_y = (HEIGHT / 3 - START_Y) / 100 * 2;
	point_set(&minimap->content_start,
		START_X + minimap->offset_x,
		START_Y + minimap->offset_y);
	point_set(&minimap->content_end,
		WIDTH / 3 - minimap->offset_x,
		HEIGHT / 3 - minimap->offset_y);
	size_y = (minimap->content_end.y - minimap->content_start.y) / scale;
	size_x = size_y;
	element_set(&minimap->element,
		size_x,
		size_y);
	point_set(&minimap->border_start,
		START_X,
		START_Y);
	point_set(&minimap->border_end,
		START_X + minimap->element.size_x * max_column + 2 * minimap->offset_x,
		START_Y + minimap->element.size_y * max_line + 2 * minimap->offset_y);
}

static void	minimap_init_fullscreen(t_minimap *minimap, double max_column,
		double max_line)
{
	t_point	mid;
	double	scale;
	double	size_x;
	double	size_y;

	minimap->offset_x = 0;
	minimap->offset_y = 0;
	scale = (double) cub_get_bigger_sizet(max_column, max_line) + (double) 1;
	point_set(&mid, WIDTH / 2, HEIGHT / 2);
	size_y = (HEIGHT - WIDTH / 100 * 10) / scale;
	size_x = size_y;
	element_set(&minimap->element, size_x, size_y);
	point_set(&minimap->content_start,
		mid.x - max_column / 2 * size_x,
		mid.y - max_line / 2 * size_y);
	point_set(&minimap->content_end,
		mid.x + max_column / 2 * size_x,
		mid.y + max_line / 2 * size_y);
	point_set(&minimap->border_start,
		mid.x - max_column / 2 * size_x - 10,
		mid.y - max_line / 2 * size_y - 10);
	point_set(&minimap->border_end,
		mid.x + max_column / 2 * size_x + 10,
		mid.y + max_line / 2 * size_y + 10);
}

void	minimap_init(t_minimap *minimap, size_t max_column, size_t max_line,
			int mode)
{
	set_array_colours(minimap->colours);
	if (mode == MODE_CORNER)
	{
		minimap_init_corner(minimap, (double) max_column, (double) max_line);
	}
	else if (mode == MODE_FULLSCREEN)
	{
		minimap_init_fullscreen(minimap, (double) max_column,
			(double) max_line);
	}
	minimap->size_x = minimap->content_end.x - minimap->content_start.x;
	minimap->size_y = minimap->content_end.y - minimap->content_start.y;
}

/* ************************************************************************** */
