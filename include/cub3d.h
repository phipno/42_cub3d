/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:43:34 by pnolte            #+#    #+#             */
/*   Updated: 2023/06/27 08:45:37 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42.h"		// needed for mlx_t, mlx_image_t, mlx_key_data_t
# include "minimap.h"	// needed for t_minimap
# include <stdlib.h>	// needed for size_t
# include <stdbool.h>	// needed for bool
//--------------------macros

// defines where all debugging information is written to
# define DEBUG_FD STDERR_FILENO

//if defined as 1, will print out all debug_*() output
# ifndef DEBUG
#  define DEBUG 0
# endif // DEBUG

// defines screen width and screen height
# define WIDTH  2560
# define HEIGHT 1440

// defines the movement_speed of the player, normal value 0.075
# define MOVEMENT_SPEED 0.075

// defines for the wall_textures for more easier understanding
# define NORTH 0
# define EAST 1
# define SOUTH 2
# define WEST 3

// define field of view, normal value 70
# define FOV 90

// define how tall the walls should be normal value 64
# define WALL_HEIGHT 70

// define how deep the raycasting algorithm should look, normal value 32
# define DEPTH_OF_FIELD 32

//--------------------structs
/// @param t_rgba a union struct that can store a colour in hex-format
/// @param colour the combined colour channel
/// @param s_rgba rgba all the single channels
typedef union u_rgba {
	int32_t	colour;
	struct s_rgba {
		uint8_t	a;
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
	} rgba;
}	t_rgba;

/// @param t_game a struct for the map
/// @param a_map a double char array that saves a map
/// @param map_collumn_max  map_collum_max * map_line_max make up the size from a_map
/// @param map_line_max map_collum_max * map_line_max make up the size from a_map
/// @param sky_color color of the sky/ceiling of the map
/// @param floor_color color of the floor of the map
/// @param mlx_wall a texture array that has the loaded textures from textures/
typedef struct s_game
{
	char			**a_map;
	size_t			map_column_max;
	size_t			map_line_max;
	t_rgba			sky_color;
	t_rgba			floor_color;
	mlx_texture_t	*mlx_wall[4];
}	t_game;

/// @param s_player a struct for plyer informations
/// @param pos Positions saves the current position on a_map array scale
/// @param start_pos Saves the start position on a_map array scale
/// @param d_pos is the position scaled by 64
/// @param offset dunno
/// @param fov Field of View
/// @param dir Direction that is update while running goes. Goes over field of view
/// @param mid_dir The Direction of the middest direction from north
/// @param ms Movement Speed of the player
typedef struct s_player
{
	t_point	pos;
	t_point start_pos;
	t_point d_pos;
	t_point offset;
	double	fov;
	double	dir;
	double	mid_dir;
	double	ms;
}	t_player;

/// @param s_all a struct for everything
/// @param per a struct for plyer informations
/// @param map a struct for the map
/// @param minimap a struct for the minimap
/// @param mlx the variable for our graphic lib
/// @param mlx_image_t images that will be send to our window
/// @param image_game image of the walls, gets drawn every frame change
/// @param image_background image of the two background colors, gets drawn once
/// @param image_player image of the player where he is on the minimap
/// @param mode the current mode of the minimap
typedef struct s_all
{
	t_player	per;
	t_game		map;
	t_minimap	minimap;
	mlx_t		*mlx;
	mlx_image_t	*image_game;
	mlx_image_t	*image_background;
	mlx_image_t *image_player;
	int			mode;
}	t_all;

//--------------------Parsing
void	cub_map_muncher(t_all *cub, char *file);
void	creation_of_map(t_game *map_info, char **da);
void	parse_map(t_game *map, char **content_split);
int		map_valid_question_mark(t_all *cub);
void	split_that_color(t_rgba *color, const char *str);
char	*sub_str_walls(const char *str);
void	get_player_start(t_all *cub);

//--------------------Game
void	cub_hook_keys(mlx_key_data_t key_data, void *context);
void	cub_hook_frame(void *context);
void	cub_update_game(t_all *all);

//--------------------Minimap
void	cub_update_minimap(t_all *all, int mode);

//--------------------MLX42
void	cub_image_init(t_all *cub, mlx_image_t **image);
void	cub_image_to_window(t_all *cub, mlx_image_t *image);
void	cub_init_mlx(t_all *all, char *argv[]);

//--------------------Utils
size_t	cub_get_bigger_sizet(size_t x, size_t y);
int		cub_get_rgba(int r, int g, int b, int a);

//--------------------Clean Up
void	cub_exit(int exit_code, int fd, char *message);
void	cub_freeee(t_all *cub);

#endif
