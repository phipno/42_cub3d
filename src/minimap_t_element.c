/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_t_element.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:08:24 by jwillert          #+#    #+#             */
/*   Updated: 2023/06/28 07:33:39 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h" // needed for t_minimap, t_minimap_element, MACROS
#include "cub3d.h"   // needed for MACROS
#include <unistd.h>  // needed for STDERR_FILENO
#include <stdio.h>   // needed for dprintf()

void	debug_print_t_element(char *name, t_minimap_element element)
{
	int	fd;

	fd = DEBUG_FD;
	if (DEBUG)
	{
		dprintf(fd, "--\n");
		dprintf(fd, "t_element: %s\n", name);
		dprintf(fd, "size_x %f\n", element.size_x);
		dprintf(fd, "size_y %f\n", element.size_y);
		dprintf(fd, "colour %d\n", element.colour);
		dprintf(fd, "--\n");
	}
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
		minimap->element.colour = minimap->colours[MAGENTA];
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
		minimap->element.colour = minimap->colours[WHITE];
	}
	else
	{
		minimap->element.colour = minimap->colours[MAGENTA];
	}
}

/* ************************************************************************** */
