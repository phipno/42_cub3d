/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:49:37 by jwillert          #+#    #+#             */
/*   Updated: 2023/06/06 14:30:57 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"			// needed for mlx_*()
#include "minimap.h"		// needed for t_point
#include "cub3d.h"			// needed for t_all
#include "ft_printf.h"		// needed for ft_printf()
#include <unistd.h>			// needed for STDERR_FILENO
#include <stdio.h>

static void	minimap_draw_element(mlx_image_t *image, size_t index_x,
	size_t index_y, t_minimap *minimap)
{
	t_point	element_start;
	t_point	element_end;
	double	x;
	double	y;

	element_start.x = minimap->content_start.x
		+ (double) index_x * minimap->element.size_x;
	element_start.y = minimap->content_start.y
		+ (double) index_y * minimap->element.size_y;
	x = element_start.x;
	y = element_start.y;
	element_end.x = element_start.x + minimap->element.size_x;
	element_end.y = element_start.y + minimap->element.size_y;
	if (minimap->flag_player == 1)
	{
		point_set_mid(&minimap->player_pos, element_start, element_end);
		minimap->flag_player = 0;
	}
	while (y < element_end.y && y < HEIGHT)
	{
		while (x < element_end.x && x < WIDTH)
		{
			mlx_put_pixel(image, (int) x, (int) y, minimap->element.colour);
			x += 1;
		}
		x = element_start.x;
		y += 1;
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
	point_draw_disc(image, minimap->player_pos, 10, minimap->colours[GREEN]);
	debug_print_t_minimap("minimap", *minimap);
}
