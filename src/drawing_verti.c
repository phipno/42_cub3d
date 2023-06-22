/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_verti.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:37:46 by pnolte            #+#    #+#             */
/*   Updated: 2023/06/22 18:00:34 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "drawing.h"

#include <math.h>

static void	looking_right_verti(t_all cub, t_raycaster *ray)
{
	double	ntan;

	ntan = -tan(ray->dir);
	ray->x = (((int)cub.per.d_pos.x >> 6) << 6) - 0.0001;
	ray->y = (cub.per.d_pos.x - ray->x) * ntan + cub.per.d_pos.y;
	ray->offset.x = -64;
	ray->offset.y = -ray->offset.x * ntan;
	ray->color = 0xAAAAAAFF;
	ray->c_d = EAST;
}

static void	looking_left_verti(t_all cub, t_raycaster *ray)
{
	double	ntan;

	ntan = -tan(ray->dir);
	ray->x = (((int)cub.per.d_pos.x >> 6) << 6) + 64;
	ray->y = (cub.per.d_pos.x - ray->x) * -tan(ray->dir) + cub.per.d_pos.y;
	ray->offset.x = 64;
	ray->offset.y = -ray->offset.x * -tan(ray->dir);
	ray->color = 0x0000AAFF;
	ray->c_d = WEST;
}

static void	looking_straight_verti(t_all cub, t_raycaster *ray, int *dof)
{
	ray->x = cub.per.d_pos.x;
	ray->y = cub.per.d_pos.y;
	*dof = DEPTH_OF_FIELD;
	ray->color = 0x444444FF;
	ray->c_d = SOUTH;
}

void	draw_rays_verti(t_all cub, t_raycaster *ray)
{
	int	dof;

	dof = 0;
	ray->dir = cub.per.dir;
	if (ray->dir > P2 && ray->dir < P3)
		looking_right_verti(cub, ray);
	if (ray->dir < P2 || ray->dir > P3)
		looking_left_verti(cub, ray);
	if (ray->dir == P2 || ray->dir == P3)
		looking_straight_verti(cub, ray, &dof);
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
