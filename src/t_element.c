/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_element.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:08:24 by jwillert          #+#    #+#             */
/*   Updated: 2023/05/30 17:15:49 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>			// needed for size_t
#include "cub_minimap.h"	// needed for t_minimap_element
#include <unistd.h>			// needed for STDERR_FILENO
#include "ft_printf.h"		// needed for ft_printf()

void	debug_print_t_element(char *name, t_minimap_element element)
{
	int	fd;

	fd = DEBUG_FD;
	ft_printf(fd, "--\n");
	ft_printf(fd, "t_element: %s\n", name);
	ft_printf(fd, "size_x %u\n", element.size_x);
	ft_printf(fd, "size_y %u\n", element.size_y);
	ft_printf(fd, "colour %d\n", element.colour);
	ft_printf(fd, "--\n");
}

void	element_set(t_minimap_element *element, size_t size_x, size_t size_y)
{
	element->size_x = size_x;
	element->size_y = size_y;
}

void	element_set_colour(t_minimap *minimap, char symbol)
{
	if (symbol == SYMBOL_EMPTY)
	{
		minimap->element.colour = minimap->colours[GREEN];
	}
	else if (symbol == SYMBOL_FLOOR)
	{
		minimap->element.colour = minimap->colours[WHITE];
	}
	else if (symbol == SYMBOL_WALL)
	{
		minimap->element.colour = minimap->colours[BLACK];
	}
	else if (symbol == 'N' || symbol == 'W' || symbol == 'E' || symbol == 'S')
	{
		minimap->element.colour = minimap->colours[YELLOW];
	}
	else
	{
		minimap->element.colour = minimap->colours[MAGENTA];
	}
}
