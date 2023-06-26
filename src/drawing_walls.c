/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:37:46 by pnolte            #+#    #+#             */
/*   Updated: 2023/06/26 16:54:49 by pnolte           ###   ########.fr       */
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

static void	initilize_shits(t_walls *wal, t_all cub, t_raycaster ray)
{
	wal->t_height = cub.map.mlx_wall[ray.c_d]->height;
	wal->texture_size = cub.map.mlx_wall[ray.c_d]->width * wal->t_height * 4;
	wal->line_h = WALL_HEIGHT * HEIGHT / ray.distance_parralel;
	wal->line_offset = HEIGHT / 2 - wal->line_h / 2;
	wal->line_at = wal->line_h;
	wal->y_step = ((double)wal->t_height / wal->line_h);
}

void draw_walls(t_all cub, int x, t_raycaster ray)
{
	t_walls	wal;
	int		y;

	fish_eye(cub, &ray);
	wal.x_off = calc_tex(cub, ray);
	initilize_shits(&wal, cub, ray);
	y = wal.line_offset;
	while (y < wal.line_offset + wal.line_h)
	{
		wal.y_off = (int)(wal.y_step * (wal.line_h - wal.line_at));
		if ((x >= 0 && x < WIDTH) && (y >= 0 && y < HEIGHT))
		{
			wal.tex_index = ((wal.y_off * wal.t_height + wal.x_off) * 4);
			if (wal.tex_index + 3 < wal.texture_size  && wal.tex_index >= 0)
				mlx_put_pixel(cub.image_game, x, y, get_rgba(
					cub.map.mlx_wall[ray.c_d]->pixels[wal.tex_index],
					cub.map.mlx_wall[ray.c_d]->pixels[wal.tex_index + 1],
					cub.map.mlx_wall[ray.c_d]->pixels[wal.tex_index + 2],
					cub.map.mlx_wall[ray.c_d]->pixels[wal.tex_index + 3]));
		}
		wal.line_at--;
		y++;
	}
}
