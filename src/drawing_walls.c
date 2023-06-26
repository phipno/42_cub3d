/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:37:46 by pnolte            #+#    #+#             */
/*   Updated: 2023/06/26 12:45:43 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "drawing.h"

#include <math.h>	// needed cos and floor

#include <stdio.h>

static void	fish_eye(t_all cub, t_raycaster *ray)
{
	double	angle;

	angle = cub.per.mid_dir * (PI / 180) - cub.per.dir;
	if (angle < 0)
		angle = angle + 2 * PI;
	if (angle > 2 * PI)
		angle = angle - 2 * PI;
	ray->distance_parralel = ray->distance_raw * cos(angle);
}

static int	calc_tex(t_all cub, t_raycaster ray)
{
	double	wallx;
	int		ret;

	ray.x = ray.x / 64;
	ray.y = ray.y / 64;
	// printf("Y:%f   Y:%d\n ", ray.x, (int)ray.x);
	if (ray.c_d == NORTH || ray.c_d == SOUTH)
		wallx = (ray.x - (int)ray.x);
	if (ray.c_d == EAST || ray.c_d == WEST)
		wallx = (ray.y - (int)ray.y);
	ret = cub.map.mlx_wall[ray.c_d]->width * wallx;
	return (ret);
}

void draw_walls(t_all cub, int x, t_raycaster ray)
{
	int line_h;
	int line_offset;
	int y;
	double y_step;
	int y_off;
	int x_off;
	int height;

	fish_eye(cub, &ray);
	height = cub.map.mlx_wall[ray.c_d]->height;
	line_h = WALL_HEIGHT * HEIGHT / ray.distance_parralel;
	line_offset = HEIGHT / 2 - line_h / 2;
	y = line_h; // Start from the topmost pixel and decrement
	x_off = calc_tex(cub, ray);
	y_step = ((double)height / line_h);
	// printf("X:%d  Y_STEP:%f  X_OFF:%d\n", x, y_step, x_off);
	while (y >= 0)
	{
		y_off = (int)(y_step * (line_h - y));
		if ((x >= 0 && x < WIDTH) && (y + line_offset >= 0 && y + line_offset < HEIGHT))
		{
			// int tex_x = (int)(x_off / 4) % cub.map.mlx_wall[ray.c_d]->width; // Texture x-coordinate
			// int tex_y = (int)(y_off / 4) % cub.map.mlx_wall[ray.c_d]->height; // Texture y-coordinate
			int tex_index = (y_off * cub.map.mlx_wall[ray.c_d]->width + x_off) * 4; // Texture index
			if (tex_index + 3 < (int)cub.map.mlx_wall[ray.c_d]->width * height * 4)
				mlx_put_pixel(cub.image_game, x, y + line_offset, get_rgba(
					cub.map.mlx_wall[ray.c_d]->pixels[tex_index],
					cub.map.mlx_wall[ray.c_d]->pixels[tex_index + 1],
					cub.map.mlx_wall[ray.c_d]->pixels[tex_index + 2],
					cub.map.mlx_wall[ray.c_d]->pixels[tex_index + 3]));
		}
		y--;
	}
}
