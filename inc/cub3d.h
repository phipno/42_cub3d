/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:43:34 by pnolte            #+#    #+#             */
/*   Updated: 2023/05/10 16:05:10 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "lib/MLX42/include/MLX42/MLX42.h"

/**
 * Main MLX handle, carries important data in regards to the program.
 * @param window The window itself.
 * @param context Abstracted opengl data.
 * @param width The width of the window.
 * @param height The height of the window.
 * @param delta_time The time difference between the previous frame and the current frame.
 */
typedef struct mlx
{
	void*		window;
	void*		context;
	int32_t		width;
	int32_t		height;
	double		delta_time;
}	mlx_t;

/**
 * s_GameInfo, stores data which defines rules and playstyle of the game.
 * @param map The passed data from .cub map files.
*/

typedef struct s_GameInfo
{
	char **map;
}	t_GameInfo;

/**
 * s_PlayerInfo, holds data which is important for player information.
*/

typedef struct s_PlayerInfo
{
	int	pos_x;
	int	pos_y
}	t_PlayerInfo;

typedef struct s_all
{
	t_PlayerInfo	per;
	t_GameInfo		map;
	mlx_t			mlx;
}	t_all;

int	cub_map_muncher(t_all a);

#endif
