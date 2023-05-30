/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:43:34 by pnolte            #+#    #+#             */
/*   Updated: 2023/05/30 15:17:01 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42.h"
# include <stdlib.h>	// needed for size_t

//--------------------parser test
#ifndef PARSING_TESTER
# define PARSING_TESTER 0
# endif // PARSING_TESTER

//--------------------properties
# define WIDTH 640
# define HEIGHT 480

//--------------------debug macros
# define DEBUG_FD STDERR_FILENO

/**
 * s_game, stores data which defines rules and playstyle of the game.
 * @param map The passed data from .cub map files.
*/

typedef union u_rgba {
	int32_t	colour;
	struct s_rgba {
		uint8_t	a;
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
	} rgba;
}	t_rgba;

typedef struct s_game
{
	char	**a_map;
	size_t	map_column_max;
	size_t	map_line_max;
	t_rgba	sky_color;
	t_rgba	floor_color;
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
	float	pos_x;
	float	pos_y;
	int		fov;
	float	direction;
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
void	split_that_color(t_rgba *color, const char *str);
void	sub_str_walls(char **write_to, const char *str);

//--------------------Drawing
void	draw_heaven_and_hell(t_all cub);
void	draw_troll(t_all cub);

//--------------------Game
void	hook_keys(mlx_key_data_t key_data, void *context);

//--------------------Colours
int		get_rgba(int r, int g, int b, int a);

//--------------------Utils
size_t	return_bigger(size_t x, size_t y);

//--------------------Clean Up
void	cub_exit(int exit_code, int fd, char *message);

#endif
