/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_minimap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:08:24 by jwillert          #+#    #+#             */
/*   Updated: 2023/05/30 19:10:12 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_minimap.h"	// needed for t_minimap, debug_*()
#include "cub3d.h"			// needed for get_rgba()
#include <unistd.h>			// needed for STDERR_FILENO
#include "ft_printf.h"		// needed for ft_printf()

#include <stdio.h>

void	debug_print_t_minimap(char *name, t_minimap minimap)
{
	int	fd;

	fd = DEBUG_FD;
	ft_printf(fd, "__________________\n");
	ft_printf(fd, "%s\n", name);
	debug_print_t_point("minimap.start", minimap.start);
	debug_print_t_point("minimap.end", minimap.start);
	debug_print_t_element("minimap.element", minimap.element);
	ft_printf(fd, "__________________\n");
}

static void	set_array_colours(int32_t *colours)
{
	colours[0] = get_rgba(255, 255, 255, 255); 	// WHITE
	colours[1] = get_rgba(0, 0, 0, 255);		// BLACK
	colours[2] = get_rgba(255, 0, 255, 255);	// MAGENTA
	colours[3] = get_rgba(255, 255, 0, 255);	// YELLOW
	colours[4] = get_rgba(0, 255, 0, 20);		// GREEN
}

void	minimap_init(t_minimap *minimap, t_game game)
{
	size_t	x;
	size_t	y;
	size_t	size;
	size_t	scale;

	scale = return_bigger(game.map_column_max, game.map_line_max);
	printf("%zu\n", scale);

	size = END_X - START_X;
	x = size / scale;
	printf("x == %zu\n", x);

	size = END_Y - START_Y;
	y = size / scale;
	printf("y == %zu\n", y);

	element_set(&minimap->element, x, y);
	point_set(&minimap->start, START_X, START_Y);
	point_set(&minimap->end, END_X + minimap->element.size_x, END_Y + minimap->element.size_y);
	set_array_colours(minimap->colours);
}
