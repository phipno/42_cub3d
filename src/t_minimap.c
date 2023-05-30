/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_minimap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:08:24 by jwillert          #+#    #+#             */
/*   Updated: 2023/05/30 14:56:42 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "cub_minimap.h"	// needed for t_minimap, debug_*()
#include <unistd.h>			// needed for STDERR_FILENO
#include "ft_printf.h"		// needed for ft_printf()

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

void	minimap_init(t_minimap *minimap, t_game game)
{
	size_t	x;
	size_t	y;
	size_t	scale;

	scale = return_bigger(game.map_column_max, game.map_line_max);
	x = END_X / scale;
	y = END_Y / scale;
	element_set(&minimap->element, x, y);
	point_set(&minimap->start, START_X, START_Y);
	point_set(&minimap->end, END_X, END_Y);
}
