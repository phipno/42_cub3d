/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert@student.42heilbronn.de            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:37:55 by jwillert          #+#    #+#             */
/*   Updated: 2023/06/16 15:31:11 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "cub3d.h"
#include "minimap.h"
#include <unistd.h>

static void	set_array_colours(int32_t *colours)
{
	colours[0] = get_rgba(255, 255, 255, 255);
	colours[1] = get_rgba(0, 0, 0, 255);
	colours[2] = get_rgba(255, 0, 255, 255);
	colours[3] = get_rgba(255, 255, 0, 255);
	colours[4] = get_rgba(0, 255, 0, 255);
}

static void	source_init_helper(t_minimap *source, double max_column, 
		double max_line)
{
	t_point	mid;
	double	scale;
	double	size_x;
	double	size_y;

	source->offset_x = 0;
	source->offset_y = 0;
	scale = (double) get_bigger_sizet(max_column, max_line);
	point_set(&mid, WIDTH / 2, HEIGHT / 2);
	size_y = HEIGHT / scale;
	size_x = WIDTH / scale;
	element_set(&source->element, size_x, size_y);
	point_set(&source->content_start,
		0,
		0);
	point_set(&source->content_end,
		WIDTH,
		HEIGHT);
}

static void	source_init(t_all *all)
{
	all->image_source = mlx_new_image(all->mlx, WIDTH, HEIGHT);
	if (all->image_source == NULL)
	{
		mlx_terminate(all->mlx);
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "image_source init");
	}
	set_array_colours(all->source.colours);
	source_init_helper(&all->source, all->map.map_column_max, 
		all->map.map_line_max);
	if (mlx_image_to_window(all->mlx, all->image_source, 0, 0) == -1)
	{
		mlx_terminate(all->mlx);
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "image_source to window");
	}
}

void	draw_source(t_all *all, t_minimap *source)
{
	char		**map;
	size_t		index_y;
	size_t		index_x;

	map = all->map.a_map;
	index_y = 0;
	index_x = 0;
	source_init(all);
	while (map[index_y] != NULL)
	{
		while (map[index_y][index_x] != '\0')
		{
			element_set_colour(source, map[index_y][index_x]);
			minimap_draw_element(all->image_source, index_x, index_y, source);
			index_x += 1;
		}
		index_x = 0;
		index_y += 1;
	}
	debug_print_t_minimap("source", *source);
}
