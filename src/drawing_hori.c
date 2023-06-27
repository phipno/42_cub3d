/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_hori.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:38:48 by pnolte            #+#    #+#             */
/*   Updated: 2023/06/27 13:31:41 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "drawing.h"

#include <math.h>

static void	looking_up_hori(t_all cub, t_raycaster *ray)
{
	double	atan;

	atan = -1 / tan(ray->dir);
	ray->y = (((int)cub.per.d_pos.y >> 6) << 6) - 0.0001;
	ray->x = (cub.per.d_pos.y - ray->y)
		* (-1 / tan(ray->dir)) + cub.per.d_pos.x;
	ray->offset.y = (int)-64;
	ray->offset.x = -ray->offset.y * (-1 / tan(ray->dir));
	ray->c_d = SOUTH;
}

static void	looking_down_hori(t_all cub, t_raycaster *ray)
{
	double	atan;

	atan = -1 / tan(ray->dir);
	ray->y = (((int)cub.per.d_pos.y >> 6) << 6) + 64;
	ray->x = (cub.per.d_pos.y - ray->y)
		* (-1 / tan(ray->dir)) + cub.per.d_pos.x;
	ray->offset.y = 64;
	ray->offset.x = -ray->offset.y * (-1 / tan(ray->dir));
	ray->c_d = NORTH;
}

static void	looking_straight_hori(t_all cub, t_raycaster *ray, int *dof)
{
	ray->x = cub.per.d_pos.x;
	ray->y = cub.per.d_pos.y;
	*dof = DEPTH_OF_FIELD;
	ray->c_d = NORTH;
}

void	draw_rays_hori(t_all cub, t_raycaster *ray)
{
	int			dof;

	dof = 0;
	ray->dir = cub.per.dir;
	if (ray->dir > M_PI)
		looking_up_hori(cub, ray);
	if (ray->dir < M_PI)
		looking_down_hori(cub, ray);
	if (ray->dir == 0 || ray->dir == M_PI)
		looking_straight_hori(cub, ray, &dof);
	while (dof < DEPTH_OF_FIELD)
	{
		ray->map.x = (int)(ray->x) >> 6;
		ray->map.y = (int)(ray->y) >> 6;
		if (ray->map.y >= 0 && ray->map.y < (int)cub.map.map_line_max
			&& ray->map.x >= 0 && ray->map.x < (int)cub.map.map_column_max
			&& cub.map.a_map[(int)ray->map.y][(int)ray->map.x] == '1')
			dof = DEPTH_OF_FIELD;
		else
		{
			ray->x += ray->offset.x;
			ray->y += ray->offset.y;
			dof++;
		}
	}
}

/* ************************************************************************** */
