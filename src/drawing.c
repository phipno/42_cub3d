/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:48:45 by pnolte            #+#    #+#             */
/*   Updated: 2023/05/31 13:17:28 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "MLX42.h"
#include "libft.h"

void	draw_heaven_and_hell(t_all cub)
{
	int x;
	int y;

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

void	draw_troll(t_all cub)
{
	int x;
	int y;

	y = 80;
	while (y < HEIGHT - 80)
	{
		x = 160;
		while (x < WIDTH - 160)
		{
			mlx_put_pixel(cub.image_game, x, y, 0x0);
			x++;
		}
		y++;
	}
	y = 140;
	while (y < HEIGHT -140)
	{
		x = 0;
		while (x < WIDTH - 160 - 160)
		{
			mlx_put_pixel(cub.image_game, x, y, 0x0);
			x++;
		}
		y++;
	}
	y = 140;
	while (y < HEIGHT -140)
	{
		x = 320;
		while (x < WIDTH)
		{
			mlx_put_pixel(cub.image_game, x, y, 0x0);
			x++;
		}
		y++;
	}
}

/* ************************************************************************** */
