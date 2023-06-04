/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:49:37 by jwillert          #+#    #+#             */
/*   Updated: 2023/06/04 14:44:33 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"			// needed for mlx_*()
#include "minimap.h"		// needed for t_point
#include "cub3d.h"			// needed for t_all
#include "ft_printf.h"		// needed for ft_printf()

#include <unistd.h>			// needed for STDERR_FILENO

static void	minimap_draw_element(mlx_image_t *image, size_t index_x,
	size_t index_y, t_minimap minimap)
{
	t_point	element_start;
	t_point	element_end;
	size_t	x;
	size_t	y;

	element_start.x = minimap.content_start.x + index_x * minimap.element.size_x;
	element_start.y = minimap.content_start.y + index_y * minimap.element.size_y;

	x = element_start.x;
	y = element_start.y;

	element_end.x = element_start.x + minimap.element.size_x;
	element_end.y = element_start.y + minimap.element.size_y;

	//debug_print_t_point("element start", element_start);
	//debug_print_t_point("element end", element_end);

	while (y <= element_end.y && y <= minimap.content_end.y && y < HEIGHT)
	{
		while (x <= element_end.x && x <= minimap.content_end.x && x < WIDTH)
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
	size_t	x;
	size_t	y;

	x = minimap.border_start.x;
	y = minimap.border_start.y;
	while (y < minimap.border_end.y)
	{
		while (x < minimap.border_end.x)
		{
			mlx_put_pixel(image, x, y, minimap.colours[MAGENTA]);
			x += 1;
		}
		x = minimap.border_start.x;
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
