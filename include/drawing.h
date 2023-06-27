/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:50:39 by pnolte            #+#    #+#             */
/*   Updated: 2023/06/27 10:24:19 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWING_H
# define DRAWING_H

# include "cub3d.h"		// needed for t_all
# include "minimap.h"	// needed for t_point

/// @brief Variables for the wall_hit calculation
/// @param x hit on x-axis
/// @param y hit on y-axis
/// @param map hit points in mapscale
/// @param offset the x and y offset for each grid
/// @param dir the ray direction for the wall hit
/// @param c_d the cardinal direction, so NORTH, EAST, SOUTH, WEST
/// @param distance_raw the distance from player pos to wall_hit
/// @param distance_parralel distance_raw * cos()
/// @param pi_half PI / 2 ---- 1/2 PI
/// @param pi_three_half 3 * PI / 2 ---- 3/2 PI
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
	double	pi_half;
	double	pi_three_half;
}	t_raycaster;

/// @brief Variables for wall texture mapping
/// @param line_h how big the wall is at the corresponding x value
/// @param line_at the current y-value for the wall
/// @param line_offset the offset from the top of the screen
/// @param y_step how big the the wall y is compared to texture height
/// @param y_off the offset which needs to be added for texture mapping
/// @param x_off the offset which needs to be added for texture mapping
/// @param t_height the texture_height
/// @param tex_index combination of y_off and x_off * 4
/// @param texture_size the texture_height * texture_width * 4
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
