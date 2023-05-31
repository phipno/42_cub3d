/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:43:34 by pnolte            #+#    #+#             */
/*   Updated: 2023/05/31 11:09:44 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42.h"		// needed for mlx_t, mlx_image_t, mlx_key_data_t
# include <stdlib.h>	// needed for size_t

//--------------------debugging

// @note defines where all debugging information is writte to
# define DEBUG_FD STDERR_FILENO

//@note if defined as 1, will print out all debug_*() output
#ifndef DEBUG
# define DEBUG 0
# endif // DEBUG

//@note if defined as 1, program exits after parsing
#ifndef PARSING_TESTER
# define PARSING_TESTER 0
# endif // PARSING_TESTER

//--------------------properties
# define WIDTH 640
# define HEIGHT 480

/**
 * s_game, stores data which defines rules and playstyle of the game.
 * @param map The passed data from .cub map files.
*/

typedef struct s_game
{
	char	**a_map;
	size_t	map_column_max;
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

//--------------------Colours
int		get_rgba(int r, int g, int b, int a);

//--------------------Utils
size_t	get_bigger_sizet(size_t x, size_t y);

//--------------------Clean Up
void	cub_exit(int exit_code, int fd, char *message);

#endif
