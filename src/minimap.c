/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:49:37 by jwillert          #+#    #+#             */
/*   Updated: 2023/06/27 08:48:19 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"			// needed for mlx_*()
#include "minimap.h"		// needed for t_point
#include "cub3d.h"			// needed for t_all and t_player
#include <unistd.h>			// needed for STDERR_FILENO

void	minimap_draw_element(mlx_image_t *image, size_t index_x,
	size_t index_y, t_minimap *mmap)
{
	t_point	el_start;
	t_point	el_end;
	t_point	el;

	point_set(&el_start,
		mmap->content_start.x + (double) index_x * mmap->element.size_x,
		mmap->content_start.y + (double) index_y * mmap->element.size_y);
	point_set(&el, el_start.x, el_start.y);
	point_set(&el_end, el_start.x + mmap->element.size_x,
		el_start.y + mmap->element.size_y);
	while (el.y < el_end.y && el.y < HEIGHT)
	{
		while (el.x < el_end.x && el.x < WIDTH)
		{
			if (el.x == el_start.x || el.x == el_end.x
				|| el.y == el_start.y || el.y == el_end.y)
				mlx_put_pixel(image, (int) el.x, (int) el.y, mmap->colours[2]);
			else
				mlx_put_pixel(image, (int) el.x,
					(int) el.y, mmap->element.colour);
			el.x += 1;
		}
		el.x = el_start.x;
		el.y += 1;
	}
}

static void	minimap_draw_border(mlx_image_t *image, t_minimap minimap)
{
	double	x;
	double	y;

	x = minimap.border_start.x;
	y = minimap.border_start.y;
	while (y < minimap.border_end.y && y < HEIGHT)
	{
		while (x < minimap.border_end.x && x < WIDTH)
		{
			mlx_put_pixel(image, (int) x, (int) y, minimap.colours[MAGENTA]);
			x += 1;
		}
		x = minimap.border_start.x;
		y += 1;
	}
}

void	minimap_draw(char **map, mlx_image_t *image, t_minimap *minimap)
{
	size_t	index_x;
	size_t	index_y;

	index_x = 0;
	index_y = 0;
	minimap_draw_border(image, *minimap);
	while (map[index_y] != NULL)
	{
		while (map[index_y][index_x] != '\0')
		{
			element_set_colour(minimap, map[index_y][index_x]);
			minimap_draw_element(image, index_x, index_y, minimap);
			index_x += 1;
		}
		index_x = 0;
		index_y += 1;
	}
	debug_print_t_minimap("minimap", *minimap);
}
