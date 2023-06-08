/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:28:07 by jwillert          #+#    #+#             */
/*   Updated: 2023/06/08 13:22:53 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"  // needed for MACROS, mlx_*(), mlx_key_data_t
#include "cub3d.h"  // needed for t_all
#include "minimap.h"// needed for macros, t_minimap
#include <unistd.h> // needed for STDERR_FILENO

static void	update_minimap(t_all *all, int mode)
{
	all->image_minimap->enabled = true;
	mlx_delete_image(all->mlx, all->image_minimap);
	all->image_minimap = mlx_new_image(all->mlx, WIDTH, HEIGHT);
	if (all->image_minimap == NULL)
	{
		mlx_terminate(all->mlx);
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "image_minimap init");
	}
	minimap_init(&all->minimap,
		all->map.map_column_max,
		all->map.map_line_max,
		mode);
	minimap_draw(all->map.a_map, all->image_minimap, &all->minimap);
	if (mlx_image_to_window(all->mlx, all->image_minimap, 0, 0) == -1)
	{
		mlx_terminate(all->mlx);
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "image_minimap to window");
	}
}	

static void	update_player_pos(t_all *all)
{
	t_point	player_pos;

	mlx_delete_image(all->mlx, all->image_player);
	all->image_player = mlx_new_image(all->mlx, WIDTH, HEIGHT);
	if (all->image_player == NULL)
	{
		mlx_terminate(all->mlx);
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "image_player init");
	}
	player_set_pos(&all->per,
		all->minimap.player_pos.x,
		all->minimap.player_pos.y);
	point_set(&player_pos,
		all->per.pos_x,
		all->per.pos_y);
	point_draw_disc(all->image_player,
		player_pos,
		all->minimap.element.size_x / 3,
		all->minimap.colours[GREEN]);
	if (mlx_image_to_window(all->mlx, all->image_player, 0, 0) == -1)
	{
		mlx_terminate(all->mlx);
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "image_player to window");
	}
}

static void	toggle_minimap(t_all *all)
{
	static size_t	i;

	i += 1;
	if (i == 1)
	{
		update_minimap(all, MODE_CORNER);
		update_player_pos(all);
	}
	else if (i == 2)
	{
		all->image_minimap->enabled = false;
		all->image_player->enabled = false;
	}
	else if (i == 3)
	{
		i = 0;
		update_minimap(all, MODE_FULLSCREEN);
		update_player_pos(all);
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
}
