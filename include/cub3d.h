/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:43:34 by pnolte            #+#    #+#             */
/*   Updated: 2023/06/20 16:59:00 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42.h"		// needed for mlx_t, mlx_image_t, mlx_key_data_t
# include <stdlib.h>	// needed for size_t
# include "minimap.h"	// needed for t_minimap

#include <stdio.h>

//--------------------macros

// defines where all debugging information is written to
# define DEBUG_FD STDERR_FILENO

//if defined as 1, will print out all debug_*() output
# ifndef DEBUG
#  define DEBUG 0
# endif // DEBUG

//if defined as 1, program exits after parsing
# ifndef PARSING_TESTER
#  define PARSING_TESTER 0
# endif // PARSING_TESTER

# define WIDTH  1920
# define HEIGHT 1080

# define PI  M_PI
# define P2  M_PI / 2
# define P3  3 * M_PI / 2

# define MOVEMENT_SPEED 0.075

# define NORTH 0
# define EAST 1
# define SOUTH 2
# define WEST 3

# define FOV 90

# define MAP_SCALE 64

# define WALL_HEIGHT 64

# define DEPTH_OF_FIELD 128

//--------------------structs

typedef union u_rgba {
	int32_t	colour;
	struct s_rgba {
		uint8_t	a;
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
	} rgba;
}	t_rgba;

/**
 * s_game, stores data which defines rules and playstyle of the game.
 * @param map The passed data from .cub map files.
*/

typedef struct s_game
{
	char	**a_map;
	size_t	map_column_max;
	size_t	map_line_max;
	t_rgba	sky_color;
	t_rgba	floor_color;
	mlx_texture_t	*mlx_wall[4];
	char			*walls[4];
}	t_game;

/**
 * @param player, holds data which is important for player information.
*/
typedef struct s_player
{
	t_point	pos;
	t_point start_pos;
	t_point d_pos;
	t_point offset;
	double	fov;
	double	direction;
	double	angle_real;
}	t_player;

typedef struct s_all
{
	t_player	per;
	t_game		map;
	t_minimap	minimap;
	t_minimap	source;
	mlx_t		*mlx;
	mlx_image_t	*image_game;
	mlx_image_t	*image_minimap;
	mlx_image_t	*image_player;
	mlx_image_t	*image_background;
	mlx_image_t	*image_source;
	int			mode;
	double		ms;
}	t_all;

//--------------------Parsing
void	cub_map_muncher(t_all *cub, char *file);
void	creation_of_map(t_game *map_info, char **da);
void	parse_map(t_game *map, char **content_split);
int		map_valid_question_mark(t_game *a);
void	split_that_color(t_rgba *color, const char *str);
char	*sub_str_walls(const char *str);

//--------------------Drawing
void	draw_heaven_and_hell(t_all cub);
void	draw_troll(t_all cub);
void	draw_player(t_all cub);
void	draw_source(t_all *all, t_minimap *source);

//--------------------Game
void	hook_keys(mlx_key_data_t key_data, void *context);
void	hook_frame(void *context);
void	player_set_pos(t_player *per, int x, int y);
void	update_minimap(t_all *all, int mode);

void	update_player_pos(t_all *all); //this function needs restructering

//--------------------Colours
int		get_rgba(int r, int g, int b, int a);

//--------------------Utils
size_t	get_bigger_sizet(size_t x, size_t y);

//--------------------Clean Up
void	cub_exit(int exit_code, int fd, char *message);

#endif
