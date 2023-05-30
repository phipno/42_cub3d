/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_element.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:08:24 by jwillert          #+#    #+#             */
/*   Updated: 2023/05/30 14:57:11 by jwillert         ###   ########          */
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

void	element_set_colour(t_minimap_element *element, char symbol)
{
	if (symbol == '0')
	{
		element->colour = COLOUR_FLOOR;
	}
	else if (symbol == '1')
	{
		element->colour = COLOUR_WALL;
	}
	else if (symbol == 'N')
	{
		element->colour = COLOUR_PLAYER;
	}
	else if (symbol == ' ')
	{
		element->colour = COLOUR_EMPTY;
	}
	else
	{
		element->colour = COLOUR_NOTFOUND;
	}
}
