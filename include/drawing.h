/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:50:39 by pnolte            #+#    #+#             */
/*   Updated: 2023/06/26 19:29:03 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWING_H
# define DRAWING_H

#include "cub3d.h"		// needed for t_all
#include "minimap.h"	// needed for t_point

#include <math.h>

// math defines for PI
# define PI  M_PI
# define P2  M_PI / 2
# define P3  3 * M_PI / 2


typedef struct s_raycaster
{
	double	x;
	double	y;
	t_point	map;
	t_point	offset;
	double	dir;
	int		c_d;
	double	distance_raw;
	double	distance_parralel;
}	t_raycaster;

typedef struct s_walls
{
	int		line_h;
	int		line_at;
	int		line_offset;
	double	y_step;
	int		y_off;
	int		x_off;
	int		t_height;
	int		tex_index;
	int		texture_size;
}	t_walls;

typedef struct s_point_int
{
	int	x;
	int	y;
}	t_point_int;

typedef struct s_dda
{
	t_point_int	delta;
	t_point		inc;
	t_point		scr;
	int			steps;
}	t_dda;

//--------------------Drawing
void	draw_heaven_and_hell(t_all cub);
void	draw_player(t_all cub);
void	draw_rays_verti(t_all cub, t_raycaster *ray);
void	draw_rays_hori(t_all cub, t_raycaster *ray);

//--------------------Walls
void	draw_walls(t_all cub, int x, t_raycaster ray);

//--------------------Utils
void	ft_dda(t_point_int fir, t_point_int sec, t_all cub, int32_t color);
double	pythagoras(float ax, float ay, float bx, float by);

#endif

/* ************************************************************************** */
