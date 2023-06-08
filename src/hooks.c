/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:28:07 by jwillert          #+#    #+#             */
/*   Updated: 2023/06/07 10:38:17 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"  // needed for MACROS, mlx_*(), mlx_key_data_t
#include "cub3d.h"  // needed for t_all
#include <unistd.h> // needed for STDERR_FILENO
#include <math.h>   // needed for cos

static void	toggle_minimap_fullscreen(t_all *all)
{
	mlx_delete_image(all->mlx, all->image_minimap);
	all->image_minimap = mlx_new_image(all->mlx, WIDTH, HEIGHT);
	if (all->image_minimap == NULL)
	{
		// @todo handle error
		mlx_terminate(all->mlx);
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "image_minimap init");
	}
	all->image_minimap->enabled = true;
	minimap_init(all->minimap, all->map.map_column_max,
		all->map.map_line_max, MODE_FULLSCREEN);
	minimap_draw(all->map.a_map, all->image_minimap, all->minimap);
}

static void	toggle_minimap_corner(t_all *all)
{
	mlx_delete_image(all->mlx, all->image_minimap);
	all->image_minimap = mlx_new_image(all->mlx, WIDTH, HEIGHT);
	if (all->image_minimap == NULL)
	{
		// @todo handle error
		mlx_terminate(all->mlx);
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "image_minimap init");
	}
	minimap_init(all->minimap, all->map.map_column_max,
		all->map.map_line_max, MODE_CORNER);
	minimap_draw(all->map.a_map, all->image_minimap, all->minimap);
}

static void	toggle_minimap(t_all *all)
{
	static size_t	i;

	i += 1;
	if (i == 1)
	{
		toggle_minimap_corner(all);
	}
	else if (i == 2)
	{
		all->image_minimap->enabled = false;
	}
	else if (i == 3)
	{
		i = 0;
		toggle_minimap_fullscreen(all);
	}
	if (i != 2)
	{
		if (mlx_image_to_window(all->mlx, all->image_minimap, 0, 0) == -1)
		{
			mlx_terminate(all->mlx);
			cub_exit(EXIT_FAILURE, STDERR_FILENO, "image_minimap to window");
		}
	}
}

void	hook_keys(mlx_key_data_t key_data, void *context)
{
	t_all	*all;

	(void) key_data;
	all = (t_all *) context;
	if (mlx_is_key_down(all->mlx, MLX_KEY_ESCAPE) == true)
	{
		mlx_close_window(all->mlx);
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_M) == true)
	{
		toggle_minimap(all);
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_W) == true)
	{
		all->per.pos.y += all->per.d_pos.y;
		all->per.pos.x += all->per.d_pos.x;
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_S) == true)
	{
		all->per.pos.y -= all->per.d_pos.y;
		all->per.pos.x -= all->per.d_pos.x;
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_A) == true)
	{
		all->per.direction -= 0.1;
		if (all->per.direction < 0)
			all->per.direction += 2 * PI;
		all->per.d_pos.x = cos(all->per.direction);
		all->per.d_pos.y = sin(all->per.direction);
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_D) == true)
	{
		all->per.direction += 0.1;
		if (all->per.direction > 2 * PI)
			all->per.direction -= 2 * PI;
		all->per.d_pos.x = cos(all->per.direction);
		all->per.d_pos.y = sin(all->per.direction);
	}
	mlx_delete_image(all->mlx, all->image_game);
	all->image_game = mlx_new_image(all->mlx, WIDTH, HEIGHT);
	if (all->image_game == NULL)
	{
		// @todo handle error
		mlx_terminate(all->mlx);
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "image_game init");
	}
	draw_heaven_and_hell(*all);
	draw_player(*all);
	if (mlx_image_to_window(all->mlx, all->image_game, 0, 0) == -1)
	{
		mlx_terminate(all->mlx);
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "image_game to window");
	}
}
