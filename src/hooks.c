/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:28:07 by jwillert          #+#    #+#             */
/*   Updated: 2023/06/23 10:47:28 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"  // needed for MACROS, mlx_*(), mlx_key_data_t

#include "cub3d.h"  // needed for t_all
#include "minimap.h"// needed for macros, t_minimap
#include "drawing.h"

#include <unistd.h> // needed for STDERR_FILENO
#include <math.h>   // needed for cos(), sin(), tan()
#include <stdio.h>  // needed for dprintf()

void	update_minimap(t_all *all, int mode)
{
	if (mode == MODE_OFF)
		return ;
	minimap_init(&all->minimap,
		all->map.map_column_max,
		all->map.map_line_max,
		mode);
	minimap_draw(all->map.a_map, all->image_game, &all->minimap);
}

void	update_game(t_all *all)
{
	if (all->image_game != NULL)
	{
		all->image_game->enabled = true;
		mlx_delete_image(all->mlx, all->image_game);
	}
	all->image_game = mlx_new_image(all->mlx, WIDTH, HEIGHT);
	if (all->image_game == NULL)
	{
		mlx_terminate(all->mlx);
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "image_game init");
	}
	draw_player(*all);
	if (mlx_image_to_window(all->mlx, all->image_game, 0, 0) == -1)
	{
		mlx_terminate(all->mlx);
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "image_game to window");
	}
}

//@note this function needs restructering
// void	update_player_pos(t_all *all)
// {
// 	t_point	player_pos;

// 	if (all->image_player != NULL)
// 		mlx_delete_image(all->mlx, all->image_player);
// 	all->image_player = mlx_new_image(all->mlx, WIDTH, HEIGHT);
// 	if (all->image_player == NULL)
// 	{
// 		mlx_terminate(all->mlx);
// 		cub_exit(EXIT_FAILURE, STDERR_FILENO, "image_player init");
// 	}
// 	player_set_pos(&all->per,
// 		all->source.player_pos.x + all->per.offset.x,
// 		all->source.player_pos.y + all->per.offset.y);
// 	point_set(&player_pos,
// 		all->per.pos.x,
// 		all->per.pos.y);
// 	point_draw_disc(all->image_player,
// 		player_pos,
// 		all->source.element.size_x / 2,
// 		all->source.colours[GREEN]);
// 	if (mlx_image_to_window(all->mlx, all->image_player, 0, 0) == -1)
// 	{
// 		mlx_terminate(all->mlx);
// 		cub_exit(EXIT_FAILURE, STDERR_FILENO, "image_player to window");
// 	}
// 	debug_print_t_point("player pos", player_pos);
// }

static void	toggle_minimap(t_all *all)
{
	static size_t	i;

	i += 1;
	if (i == 1)
	{
		all->mode = MODE_FULLSCREEN;
	}
	else if (i == 2)
	{
		all->mode = MODE_CORNER;
	}
	else if (i == 3)
	{
		all->mode = MODE_OFF;
		i = 0;
	}
	update_game(all);
	update_minimap(all, all->mode);
}

static int	hook_movement(t_all *all)
{
	bool	x;
	bool	y;

	x = false;
	y = false;
	if (mlx_is_key_down(all->mlx, MLX_KEY_W) == true)
	{

		if (all->map.a_map[(int)(all->per.pos.y + sin((all->per.mid_dir) / 180 * M_PI) * all->per.ms)][(int)(all->per.pos.x + cos((all->per.mid_dir) / 180 * M_PI) * all->per.ms)] != '1')
		{
			all->per.pos.x += cos((all->per.mid_dir) / 180 * M_PI) * all->per.ms;
			all->per.pos.y += sin((all->per.mid_dir) / 180 * M_PI) * all->per.ms;
		}
		y = true;
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_S) == true)
	{
		if (all->map.a_map[(int)(all->per.pos.y + sin((all->per.mid_dir - 180) / 180 * M_PI) * all->per.ms)][(int)(all->per.pos.x + cos((all->per.mid_dir - 180) / 180 * M_PI) * all->per.ms)] != '1')
		{
			all->per.pos.x += cos((all->per.mid_dir - 180) / 180 * M_PI) * all->per.ms;
			all->per.pos.y += sin((all->per.mid_dir - 180) / 180 * M_PI) * all->per.ms;
		}
		y = true;
	}
	if (mlx_is_key_down(all->mlx, MLX_KEY_D) == true)
	{
		if (all->map.a_map[(int)(all->per.pos.y + sin((all->per.mid_dir + 90) / 180 * M_PI) * all->per.ms)][(int)(all->per.pos.x + cos((all->per.mid_dir + 90) / 180 * M_PI) * all->per.ms)] != '1')
		{
			all->per.pos.x += cos((all->per.mid_dir + 90) / 180 * M_PI) * all->per.ms;
			all->per.pos.y += sin((all->per.mid_dir + 90) / 180 * M_PI) * all->per.ms;
		}
		x = true;
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_A) == true)
	{
		if (all->map.a_map[(int)(all->per.pos.y + sin((all->per.mid_dir - 90) / 180 * M_PI) * all->per.ms)][(int)(all->per.pos.x + cos((all->per.mid_dir - 90) / 180 * M_PI) * all->per.ms)] != '1')
		{
			all->per.pos.x += cos((all->per.mid_dir - 90) / 180 * M_PI) * all->per.ms;
			all->per.pos.y += sin((all->per.mid_dir - 90) / 180 * M_PI) * all->per.ms;
		}
		x = true;
	}
	if (mlx_is_key_down(all->mlx, MLX_KEY_LEFT) == true)
	{
//		all->per.direction -= 0.1;
		if (all->per.mid_dir < 0)
			all->per.mid_dir += 360;
		all->per.mid_dir -= 5;
		x = true;
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_RIGHT) == true)
	{
//		all->per.direction += 0.1;
		if (all->per.mid_dir > 360)
			all->per.mid_dir = 0;
		all->per.mid_dir += 5;
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
	//@note commented out // blinking player position
	// if (frame == 10)
	// {
	// 	if (all->image_player->enabled == false && all->mode != MODE_OFF)
	// 	{
	// 		all->image_player->enabled = true;
	// 	}
	// 	else
	// 	{
	// 		all->image_player->enabled = false;
	// 	}
	// 	frame = 0;
	// }
	// @todo make movement smoother, some random acceleration
	// (mb limit frames that we check)

	if (hook_movement(all) == true)
	{
		update_game(all);
		update_minimap(all, all->mode);
	}
}

void	hook_keys(mlx_key_data_t key_data, void *context)
{
	t_all	*all;

	all = (t_all *) context;
	if (key_data.key == MLX_KEY_LEFT_SHIFT && key_data.action == MLX_PRESS)
	{
		all->per.ms += 0.05;
	}
	if (key_data.key == MLX_KEY_LEFT_SHIFT && key_data.action == MLX_RELEASE)
	{
		all->per.ms -= 0.05;
	}
	if (mlx_is_key_down(all->mlx, MLX_KEY_ESCAPE) == true)
	{
		mlx_close_window(all->mlx);
	}
	else if (key_data.key == MLX_KEY_M && key_data.action == MLX_PRESS)
	{
		toggle_minimap(all);
	}
}
