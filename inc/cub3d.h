/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:43:34 by pnolte            #+#    #+#             */
/*   Updated: 2023/05/22 10:54:02 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "MLX42.h"

/**
 * Main MLX handle, carries important data in regards to the program.
 * @param window The window itself.
 * @param context Abstracted opengl data.
 * @param width The width of the window.
 * @param height The height of the window.
 * @param delta_time The time difference between the previous frame and the current frame.
 */
typedef struct s_mlx
{
	void*		window;
	void*		context;
	int32_t		width;
	int32_t		height;
	double		delta_time;
}	t_mlx;

/**
 * s_GameInfo, stores data which defines rules and playstyle of the game.
 * @param map The passed data from .cub map files.
*/

typedef struct s_GameInfo
{
	char	**map;
	int		sky_color[3];
	int		floor_color[3];
	char	*north_wall;
	char	*east_wall;
	char	*south_wall;
	char	*west_wall;
}	t_GameInfo;

/**
 * s_PlayerInfo, holds data which is important for player information.
*/

typedef struct s_PlayerInfo
{
	int	pos_x;
	int	pos_y;
}	t_PlayerInfo;

typedef struct s_all
{
	t_PlayerInfo	per;
	t_GameInfo		map;
	t_mlx			mlx;
}	t_all;

int	cub_map_muncher(t_all *a, char *argv[]);

#endif
