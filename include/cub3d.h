/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:43:34 by pnolte            #+#    #+#             */
/*   Updated: 2023/05/24 15:17:36 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42.h"
# include <stdlib.h>	// needed for size_t


//--------------------Properties
# define WIDTH 640
# define HEIGHT 480



/**
 * Main MLX handle, carries important data in regards to the program.
 * @param window The window itself.
 * @param context Abstracted opengl data.
 * @param width The width of the window.
 * @param height The height of the window.
 * @param delta_time The time difference between the previous frame and the
 * current frame.
 */
// typedef struct s_mlx
// {
// 	void*		window;
// 	void*		context;
// 	int32_t		width;
// 	int32_t		height;
// 	double		delta_time;
// }	t_mlx;

/**
 * s_game, stores data which defines rules and playstyle of the game.
 * @param map The passed data from .cub map files.
*/

typedef struct s_game
{
	char	**a_map;
	size_t	map_collum_max;
	size_t	map_line_max;
	int		sky_color[3];
	int		floor_color[3];
	char	*north_wall;
	char	*east_wall;
	char	*south_wall;
	char	*west_wall;
}	t_game;

/**
 * s_player, holds data which is important for player information.
*/

typedef struct s_player
{
	int	pos_x;
	int	pos_y;
}	t_player;

typedef struct s_all
{
	t_player	per;
	t_game		map;
	mlx_t		*mlx;
	mlx_image_t	*image;
}	t_all;

//--------------------Parsing

void	cub_map_muncher(t_all *cub, char *file);
void	creation_of_map(t_game *map_info, char **da);
void	parse_map(t_game *map, char **content_split);
int		map_valid_question_mark(t_game *a);

int		split_that_color(int write_to[3], const char *str);
int		sub_str_walls(char **write_to, const char *str);

//--------------------Game
void	hook_keys(mlx_key_data_t key_data, void *context);

//--------------------Clean Up
void	cub_exit(int exit_code, int fd, char *message);

#endif
