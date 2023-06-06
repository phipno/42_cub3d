/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:48:45 by pnolte            #+#    #+#             */
/*   Updated: 2023/06/06 19:36:44 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "MLX42.h"
#include "libft.h"
#include "raycasting.h"

void	draw_heaven_and_hell(t_all cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				mlx_put_pixel(cub.image_game, x, y, cub.map.sky_color.colour);
			else
				mlx_put_pixel(cub.image_game, x, y, cub.map.floor_color.colour);
			x++;
		}
		y++;
	}
}

void	castcast(t_game map, t_player per, mlx_image_t *image)
{
	bool	is_wall;
	float	y;
	float	x;

	is_wall = false;
	while (is_wall != true)
	{

		y = per.pos_y + 1;
		x = per.pox_x + (per.pos_y - (int)y) / tan()
		if (map.a_map[(int)y][(int)x] == '1')
			is_wall = true;
	}
}

void	caster_of_rai(t_game map, t_player per, mlx_image_t *image)
{
	t_raycasting ray;

	ray.screen_y = 0;
	ray.dir = per.direction - per.fov / 2;
	ray.add = per.fov / WIDTH;
	while (ray.y < WIDTH)
	{
		castcast(map, per, image, ray);
		ray.dir = ray.dir + ray.add;
		y++;
	}
}
// void	draw_troll(t_all cub)
// {
// 	int x;
// 	int y;

// 	y = 80;
// 	while (y < HEIGHT - 80)
// 	{
// 		x = 160;
// 		while (x < WIDTH - 160)
// 		{
// 			mlx_put_pixel(cub.image, x, y, 0x0);
// 			x++;
// 		}
// 		y++;
// 	}
// 	y = 140;
// 	while (y < HEIGHT -140)
// 	{
// 		x = 0;
// 		while (x < WIDTH - 160 - 160)
// 		{
// 			mlx_put_pixel(cub.image, x, y, 0x0);
// 			x++;
// 		}
// 		y++;
// 	}
// 	y = 140;
// 	while (y < HEIGHT -140)
// 	{
// 		x = 320;
// 		while (x < WIDTH)
// 		{
// 			mlx_put_pixel(cub.image, x, y, 0x0);
// 			x++;
// 		}
// 		y++;
// 	}
// }

/* ************************************************************************** */
