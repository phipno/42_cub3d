/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:48:45 by pnolte            #+#    #+#             */
/*   Updated: 2023/06/22 15:23:11 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "MLX42.h"
#include "libft.h"
#include "drawing.h"

#include <math.h>

#include <stdio.h> //for debugging

void DDA(t_point_int fir, t_point_int sec, t_all cub, int32_t color)
{
	t_dda dda;

	dda.delta.x = sec.x - fir.x;
	dda.delta.y = sec.y - fir.y;
	dda.steps = abs(dda.delta.x) > abs(dda.delta.y) ? abs(dda.delta.x) : abs(dda.delta.y);
	dda.inc.x = dda.delta.x / (float)dda.steps;
	dda.inc.y = fir.y / (float)dda.steps;
	dda.scr.x = fir.x;
	dda.scr.y = fir.y;
	for (int i = 0; i <= dda.steps; i++) {
		if ((dda.scr.x >= 0 && dda.scr.x < WIDTH) && (dda.scr.y >= 0 && dda.scr.y < HEIGHT))
			mlx_put_pixel(cub.image_player, dda.scr.x, dda.scr.y, color);
		dda.scr.x += dda.inc.x;
		dda.scr.y += dda.inc.y;
	}
}

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
				mlx_put_pixel(cub.image_background, x, y,
					cub.map.sky_color.colour);
			else
				mlx_put_pixel(cub.image_background, x, y,
					cub.map.floor_color.colour);
			x++;
		}
		y++;
	}
}

double	pythagoras(float ax, float ay, float bx, float by)
{
	return (sqrt(( bx - ax ) * ( bx - ax ) + (by - ay) * (by - ay)));
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}


// angle fixes the distortion from walls on the same
// grid line not being displayed on the same y height
// in short fixes fish eye

void	draw_player(t_all cub)
{
	double	angle_add;
	t_raycaster rays[2];

	cub.per.d_pos.x = cub.per.pos.x * MAP_SCALE;
	cub.per.d_pos.y = cub.per.pos.y * MAP_SCALE;
	angle_add = (FOV * (PI / 180)) / WIDTH * 1.0;
	cub.per.direction = (cub.per.angle_real * (PI / 180)) - (FOV * (PI / 180)) / 2;
	for (int x = 0; x < WIDTH; x++)
	{
		if (cub.per.direction < 0)
			cub.per.direction = cub.per.direction + 2 * PI;
		if (cub.per.direction > 2 * PI)
			cub.per.direction = cub.per.direction - 2 * PI;
		draw_rays_hori(cub, &rays[0]);
		draw_rays_verti(cub, &rays[1]);
		if (rays[0].distance_raw < rays[1].distance_raw)
			draw_walls(cub, x, rays[0]);
		else
			draw_walls(cub, x, rays[1]);
		cub.per.direction += angle_add;
	}
}

/* ************************************************************************** */
