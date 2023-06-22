/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:37:46 by pnolte            #+#    #+#             */
/*   Updated: 2023/06/22 18:00:43 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "drawing.h"

#include <math.h>

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

static void	texture_mapping(t_all cub, t_raycaster ray)
{
	int			x_offset;

	x_offset = 0;
	if (ray.c_d == NORTH || ray.c_d == SOUTH)
	{
		x_offset = (ray.map.x + ray.distance_parralel * ray.dir
				- (int)ray.map.x) * cub.map.mlx_wall[ray.c_d]->width * 4;
	}
	else if (ray.c_d == EAST || ray.c_d == WEST)
	{
		x_offset = (ray.map.y + ray.distance_parralel * ray.dir
				- (int)ray.map.y) * cub.map.mlx_wall[ray.c_d]->width * 4;
	}
	x_offset = cub.map.mlx_wall[ray.c_d]->width - x_offset - 1;
}

void	draw_walls(t_all cub, int x, t_raycaster ray)
{
	int		line_h;
	int		line_offset;

	fish_eye(cub, &ray);
	texture_mapping(cub, ray);
	line_h = WALL_HEIGHT * HEIGHT / ray.distance_parralel;
	if (line_h > HEIGHT)
		line_h = HEIGHT;
	line_offset = HEIGHT / 2 - line_h / 2;
	while (line_h >= 0)
	{
		if ((x >= 0 && x < WIDTH) && (line_h + line_offset >= 0
				&& line_h + line_offset < HEIGHT))
			mlx_put_pixel(cub.image_game, x, line_h + line_offset, get_rgba(
					cub.map.mlx_wall[ray.c_d]->pixels[0],
					cub.map.mlx_wall[ray.c_d]->pixels[1],
					cub.map.mlx_wall[ray.c_d]->pixels[2],
					cub.map.mlx_wall[ray.c_d]->pixels[3]));
		line_h--;
	}
}
