/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 21:23:46 by jwillert          #+#    #+#             */
/*   Updated: 2023/06/27 08:37:22 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"  // needed for MACROS, mlx_*(), mlx_key_data_t
#include "cub3d.h"  // needed for t_all
#include "minimap.h"// needed for macros, t_minimap
#include "drawing.h"
#include <unistd.h> // needed for STDERR_FILENO
#include <math.h>   // needed for cos(), sin(), tan()
#include <stdio.h>  // needed for dprintf()

#define FORWARD 1
#define BACKWARD 2
#define RIGHT 1
#define LEFT 2

static void	move_bilateral(t_all *all, int movement)
{
	double	x_mov;
	double	y_mov;

	if (movement == FORWARD)
	{
		x_mov = cos((all->per.mid_dir) / 180 * M_PI) * all->per.ms;
		y_mov = sin((all->per.mid_dir) / 180 * M_PI) * all->per.ms;
		if (all->map.a_map[(int)(all->per.pos.y + y_mov + (y_mov * 5))]
			[(int)(all->per.pos.x)] != '1')
			all->per.pos.y += y_mov;
		if (all->map.a_map[(int)(all->per.pos.y)]
			[(int)(all->per.pos.x + x_mov + (x_mov * 5))] != '1')
			all->per.pos.x += x_mov;
	}
	else if (movement == BACKWARD)
	{
		x_mov = cos((all->per.mid_dir - 180) / 180 * M_PI) * all->per.ms;
		y_mov = sin((all->per.mid_dir - 180) / 180 * M_PI) * all->per.ms;
		if (all->map.a_map[(int)(all->per.pos.y + y_mov + (y_mov * 5))]
			[(int)(all->per.pos.x)] != '1')
			all->per.pos.y += y_mov;
		if (all->map.a_map[(int)(all->per.pos.y)]
			[(int)(all->per.pos.x + x_mov + (x_mov * 5))] != '1')
			all->per.pos.x += x_mov;
	}
}

static void	move_unilateral(t_all *all, int movement)
{
	double	x_mov;
	double	y_mov;

	if (movement == RIGHT)
	{
		x_mov = cos((all->per.mid_dir + 90) / 180 * M_PI) * all->per.ms;
		y_mov = sin((all->per.mid_dir + 90) / 180 * M_PI) * all->per.ms;
		if (all->map.a_map[(int)(all->per.pos.y + y_mov + (y_mov * 5))]
			[(int)(all->per.pos.x)] != '1')
			all->per.pos.y += y_mov;
		if (all->map.a_map[(int)(all->per.pos.y)]
			[(int)(all->per.pos.x + x_mov + (x_mov * 5))] != '1')
			all->per.pos.x += x_mov;
	}
	else if (movement == LEFT)
	{
		x_mov = cos((all->per.mid_dir - 90) / 180 * M_PI) * all->per.ms;
		y_mov = sin((all->per.mid_dir - 90) / 180 * M_PI) * all->per.ms;
		if (all->map.a_map[(int)(all->per.pos.y + y_mov + (y_mov * 5))]
			[(int)(all->per.pos.x)] != '1')
			all->per.pos.y += y_mov;
		if (all->map.a_map[(int)(all->per.pos.y)]
			[(int)(all->per.pos.x + x_mov + (x_mov * 5))] != '1')
			all->per.pos.x += x_mov;
	}
}

static bool	hook_movement(t_all *all)
{
	bool	is_movement;

	is_movement = false;
	if (mlx_is_key_down(all->mlx, MLX_KEY_W) == true)
	{
		move_bilateral(all, FORWARD);
		is_movement = true;
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_S) == true)
	{
		move_bilateral(all, BACKWARD);
		is_movement = true;
	}
	if (mlx_is_key_down(all->mlx, MLX_KEY_D) == true)
	{
		move_unilateral(all, RIGHT);
		is_movement = true;
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_A) == true)
	{
		move_unilateral(all, LEFT);
		is_movement = true;
	}
	return (is_movement);
}

static bool	hook_turn(t_all *all)
{
	bool	is_turn;

	is_turn = false;
	if (mlx_is_key_down(all->mlx, MLX_KEY_LEFT) == true)
	{
		if (all->per.mid_dir < 0)
			all->per.mid_dir += 360;
		all->per.mid_dir -= 5;
		is_turn = true;
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_RIGHT) == true)
	{
		if (all->per.mid_dir > 360)
			all->per.mid_dir = 0;
		all->per.mid_dir += 5;
		is_turn = true;
	}
	return (is_turn);
}

void	cub_hook_frame(void *context)
{
	t_all		*all;
	bool		redraw;

	all = (t_all *) context;
	redraw = false;
	if (hook_movement(all) == true)
	{
		redraw = true;
	}
	if (hook_turn(all) == true)
	{
		redraw = true;
	}
	if (redraw == true)
	{
		cub_update_game(all);
		cub_update_minimap(all, all->mode);
	}
}
