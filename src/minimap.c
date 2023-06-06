/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:49:37 by jwillert          #+#    #+#             */
/*   Updated: 2023/06/07 00:16:33 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"			// needed for mlx_*()
#include "minimap.h"		// needed for t_point
#include "cub3d.h"			// needed for t_all and t_player
#include "ft_printf.h"		// needed for ft_printf()
#include <unistd.h>			// needed for STDERR_FILENO

#include <stdio.h>

static void	minimap_draw_grid(mlx_image_t *image, size_t index_x,
	size_t index_y, t_minimap *minimap)
{
	t_point	element_start;
	t_point	element_end;
	t_point	element;
	t_point element2;

	point_set(&element_start,
		minimap->content_start.x + (double) index_x * minimap->element.size_x,
		minimap->content_start.y + (double) index_y * minimap->element.size_y);
	point_set(&element, element_start.x, element_start.y);
	point_set(&element_end,
		element_start.x + minimap->element.size_x,
		element_start.y + minimap->element.size_y);
	element2 = element;
	if (minimap->flag_player == 1)
		point_set_mid(&minimap->player_pos, element_start, element_end);
	while (element.x < element_end.x && element.x < WIDTH)
	{
		mlx_put_pixel(image,
			(int) element.x, (int) element.y, minimap->colours[2]);
		mlx_put_pixel(image,
			(int) element.x, (int) element.y + minimap->element.size_y, minimap->colours[2]);
		element.x += 1;
	}
	while (element2.y < element_end.y && element2.y < HEIGHT)
	{
		mlx_put_pixel(image,
			(int) element2.x, (int) element2.y, minimap->colours[2]);
		mlx_put_pixel(image,
			(int) element2.x + minimap->element.size_x, (int) element2.y, minimap->colours[2]);
		element2.y += 1;
	}
}

static void	minimap_draw_element(mlx_image_t *image, size_t index_x,
	size_t index_y, t_minimap *minimap)
{
	t_point	element_start;
	t_point	element_end;
	t_point	element;

	point_set(&element_start,
		minimap->content_start.x + (double) index_x * minimap->element.size_x,
		minimap->content_start.y + (double) index_y * minimap->element.size_y);
	point_set(&element, element_start.x, element_start.y);
	point_set(&element_end,
		element_start.x + minimap->element.size_x,
		element_start.y + minimap->element.size_y);
	if (minimap->flag_player == 1)
		point_set_mid(&minimap->player_pos, element_start, element_end);
	while (element.y < element_end.y && element.y < HEIGHT)
	{
		while (element.x < element_end.x && element.x < WIDTH)
		{
			mlx_put_pixel(image,
				(int) element.x, (int) element.y, minimap->element.colour);
			element.x += 1;
		}
		element.x = element_start.x;
		element.y += 1;
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

void	minimap_draw(t_point per, char **map, mlx_image_t *image, t_minimap *minimap)
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
			minimap_draw_grid(image, index_x, index_y, minimap);
			if (minimap->flag_player == 1)
				minimap->flag_player = 0;
			index_x += 1;
		}
		index_x = 0;
		index_y += 1;
	}
	// per.x = (per.x * minimap->size_x) + minimap->offset_x;
	// per.y = (per.y * minimap->size_y) + minimap->offset_x;
	point_draw_disc(image, per, minimap->element.size_x / 2,
		minimap->colours[GREEN]);
	debug_print_t_minimap("minimap", *minimap);
}
