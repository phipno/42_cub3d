/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:49:37 by jwillert          #+#    #+#             */
/*   Updated: 2023/05/31 10:53:52 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"			// needed for mlx_*()
#include "minimap.h"	// needed for t_point
#include "cub3d.h"			// needed for t_all
#include "ft_printf.h"		// needed for ft_printf()
#include <unistd.h>			// needed for STDERR_FILENO

#include <stdio.h>			// needed for printf()

static void	minimap_draw_element(mlx_image_t *image, size_t index_x,
	size_t index_y, t_minimap minimap)
{
	t_point	element_start;
	t_point	element_end;
	size_t	x;
	size_t	y;

	x = START_X + (index_x * minimap.element.size_x + minimap.element.size_x);
	y = START_Y + (index_y * minimap.element.size_y + minimap.element.size_y);
	point_set(&element_start, x, y);
	point_set(&element_end, x + minimap.element.size_x,
		y + minimap.element.size_y);
	while (y < element_end.y && y < HEIGHT)
	{
		while (x < element_end.x && x < WIDTH)
		{
			mlx_put_pixel(image, x, y, minimap.element.colour);
			x += 1;
		}
		x = element_start.x;
		y += 1;
	}
}

static void	minimap_draw_border(mlx_image_t *image, t_minimap minimap)
{
	t_point	start;
	t_point	end;
	size_t	x;
	size_t	y;

	point_set(&start, START_X, START_Y);
	point_set(&end, END_X + minimap.element.size_x,
		END_Y + minimap.element.size_y);
	x = start.x;
	y = start.y;
	while (y < end.y + minimap.element.size_y)
	{
		while (x < end.x + minimap.element.size_x)
		{
			mlx_put_pixel(image, x, y, minimap.colours[MAGENTA]);
			x += 1;
		}
		x = start.x;
		y += 1;
	}
}

void	minimap_draw(char **map, mlx_image_t *image, t_minimap minimap)
{
	size_t	index_x;
	size_t	index_y;

	index_x = 0;
	index_y = 0;
	minimap_draw_border(image, minimap);
	while (map[index_y] != NULL)
	{
		while (map[index_y][index_x] != '\0')
		{
			element_set_colour(&minimap, map[index_y][index_x]);
			minimap_draw_element(image, index_x, index_y, minimap);
			index_x += 1;
		}
		index_x = 0;
		index_y += 1;
	}
}
