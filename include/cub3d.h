/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:43:34 by pnolte            #+#    #+#             */
/*   Updated: 2023/06/08 14:35:08 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42.h"		// needed for mlx_t, mlx_image_t, mlx_key_data_t
# include <stdlib.h>	// needed for size_t
# include "minimap.h"	// needed for t_minimap

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

# define MOVEMENT_SPEED 3

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

typedef struct s_player
{
	float	pos_x;
	float	pos_y;
	double	x;
	double	y;
	double	offset_x;
	double	offset_y;
	int		fov;
	float	direction;
}	t_player;

typedef struct s_all
{
	t_player	per;
	t_game		map;
	t_minimap	minimap;
	mlx_t		*mlx;
	mlx_image_t	*image_game;
	mlx_image_t	*image_minimap;
	mlx_image_t	*image_player;
	int			mode;
	double		ms;
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
void	hook_frame(void *context);
void	player_set_pos(t_player *per, int x, int y);
void	update_player_pos(t_all *all);
void	update_minimap(t_all *all, int mode);

//--------------------Colours
int		get_rgba(int r, int g, int b, int a);

//--------------------Utils
size_t	get_bigger_sizet(size_t x, size_t y);

//--------------------Clean Up
void	cub_exit(int exit_code, int fd, char *message);

#endif
