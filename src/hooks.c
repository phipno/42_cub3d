/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:28:07 by jwillert          #+#    #+#             */
/*   Updated: 2023/06/08 14:25:09 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"  // needed for MACROS, mlx_*(), mlx_key_data_t
#include "cub3d.h"  // needed for t_all
#include "minimap.h"// needed for macros, t_minimap
#include <unistd.h> // needed for STDERR_FILENO
#include <stdio.h>  // needed for dprintf()
void	update_minimap(t_all *all, int mode)
{
	if (all->image_minimap != NULL)
	{
		all->image_minimap->enabled = true;
		mlx_delete_image(all->mlx, all->image_minimap);
	}
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

void	update_player_pos(t_all *all)
{
	t_point	player_pos;

	if (all->image_player != NULL)
		mlx_delete_image(all->mlx, all->image_player);
	all->image_player = mlx_new_image(all->mlx, WIDTH, HEIGHT);
	if (all->image_player == NULL)
	{
		mlx_terminate(all->mlx);
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "image_player init");
	}
	player_set_pos(&all->per,
		all->minimap.player_pos.x + all->per.offset_x,
		all->minimap.player_pos.y + all->per.offset_y);
	point_set(&player_pos,
		all->per.pos_x,
		all->per.pos_y);
	point_draw_disc(all->image_player,
		player_pos,
		all->minimap.element.size_x / 1.3,
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
		all->mode = MODE_CORNER;
		update_minimap(all, all->mode);
		update_player_pos(all);
	}
	else if (i == 2)
	{
		all->mode = MODE_OFF;
		all->image_minimap->enabled = false;
		all->image_player->enabled = false;
	}
	else if (i == 3)
	{
		i = 0;
		all->mode = MODE_FULLSCREEN;
		update_minimap(all, all->mode);
		update_player_pos(all);
	}
}
static int	hook_movement(t_all *all)
{
	bool	x;
	bool	y;
	
	x = false;
	y = false;
	if (mlx_is_key_down(all->mlx, MLX_KEY_W) == true)
	{
		all->per.offset_y -= 1;
		y = true;
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_S) == true)
	{
		all->per.offset_y += 1;
		y = true;
	}
	if (mlx_is_key_down(all->mlx, MLX_KEY_D) == true)
	{
		all->per.offset_x += 1;
		x = true;
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_A) == true)
	{
		all->per.offset_x -= 1;
		x = true;
	}
	if (x == true || y == true)
		return (1);
	return (0);
}

void	hook_frame(void *context)
{
	static int	frame;
	t_all		*all;

	all = (t_all *) context;
	frame += 1;
	if (frame == 10)
	{
		if (all->image_player->enabled == false && all->mode != MODE_OFF)
		{
			all->image_player->enabled = true;
		}
		else
		{
			all->image_player->enabled = false;
		}
		frame = 0;
	}
	if (hook_movement(all) == true)
	{
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
