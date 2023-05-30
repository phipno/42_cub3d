/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:49:37 by jwillert          #+#    #+#             */
/*   Updated: 2023/05/30 14:53:33 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"			// needed for mlx_*()
#include "cub_minimap.h"	// needed for t_point
#include "cub3d.h"			// needed for t_all
#include "ft_printf.h"		// needed for ft_printf()
#include <stdio.h>			// needed for printf()
#include <unistd.h>			// needed for STDERR_FILENO

static void	minimap_draw_element(mlx_image_t *image, size_t x, size_t y,
	t_minimap minimap)
{
	t_point	start;
	t_point	end;

	x = x * minimap.element.size_x + minimap.element.size_x;
	y = y * minimap.element.size_y + minimap.element.size_y;
	point_set(&start, x, y);
	point_set(&end, x + minimap.element.size_x, y + minimap.element.size_y);
	while (y < end.y)
	{
		while (x < end.x)
		{
			mlx_put_pixel(image, x, y, minimap.element.colour);
			x += 1;
		}
		x = start.x;
		y += 1;
	}
}

int	minimap_draw(char **map, mlx_image_t *image, t_minimap minimap)
{
	size_t	index_x;
	size_t	index_y;

	index_x = 0;
	index_y = 0;
	while (map[index_y] != NULL)
	{
		while (map[index_y][index_x] != '\0')
		{
			element_set_colour(&minimap.element, map[index_y][index_x]);
			minimap_draw_element(image, index_x, index_y, minimap);
			index_x += 1;
		}
		index_x = 0;
		index_y += 1;
	}
	return (EXIT_SUCCESS);
}
