/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:37:46 by pnolte            #+#    #+#             */
/*   Updated: 2023/06/23 12:05:29 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "drawing.h"

#include <math.h>	// needed cos and floor

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

	ret = 0;
	if (ray.c_d == NORTH || ray.c_d == SOUTH)
		wallx = cub.per.d_pos.x + ray.distance_parralel * cub.per.dir;
	if (ray.c_d == EAST || ray.c_d == WEST)
		wallx = cub.per.d_pos.y + ray.distance_parralel * cub.per.dir;
	wallx -= floor(wallx);
	ret = (int)wallx * cub.map.mlx_wall[ray.c_d]->width;
	return (ret);
}

void	draw_walls(t_all cub, int x, t_raycaster ray)
{
	int		line_h;
	int		line_offset;
	int		y;
	int		tey;
	int		tex;
	int		height;

	fish_eye(cub, &ray);
	height = cub.map.mlx_wall[ray.c_d]->height;
	line_h = WALL_HEIGHT * HEIGHT / ray.distance_parralel;
	if (line_h > HEIGHT)
		line_h = HEIGHT;
	line_offset = HEIGHT / 2 - line_h / 2;
	y = line_h;
	tex = calc_tex(cub, ray);
	while (y >= 0)
	{
		tey = line_offset + height - 1;
		if ((x >= 0 && x < WIDTH) && (line_h + line_offset >= 0
				&& line_h + line_offset < HEIGHT))
			mlx_put_pixel(cub.image_game, x, line_h + line_offset, get_rgba(
					cub.map.mlx_wall[ray.c_d]->pixels[(tey * height + tex) * 4],
					cub.map.mlx_wall[ray.c_d]->pixels[(tey * height + tex) * 4],
					cub.map.mlx_wall[ray.c_d]->pixels[(tey * height + tex) * 4],
					cub.map.mlx_wall[ray.c_d]->pixels[(tey * height + tex) * 4]));
		y--;
	}
}
