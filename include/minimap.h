/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:45:22 by jwillert          #+#    #+#             */
/*   Updated: 2023/05/31 16:40:27 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

/* -------------------------------------------------------------------------- */
//								includes
/* -------------------------------------------------------------------------- */

# include "MLX42.h"		// needed for mlx_image_t
# include <stdlib.h>	// needed for size_t

/* -------------------------------------------------------------------------- */
//								macros
/* -------------------------------------------------------------------------- */

// start and end location of minimap in pixel
# define START_X  0
# define START_Y  0
# define END_X    120
# define END_Y    120
# define MINIMAP_OFFSET 10

// modes for the minimap
# define MODE_OFF         0
# define MODE_CORNER      1
# define MODE_FULLSCREEN  2

// macros for game.map symbols
# define SYMBOL_FLOOR  '0'
# define SYMBOL_WALL   '1'
# define SYMBOL_EMPTY  ' '

// indexes for colour array in minimap.colours[5]
# define WHITE   0
# define BLACK   1
# define MAGENTA 2
# define YELLOW  3
# define GREEN   4

/* -------------------------------------------------------------------------- */
//								structs
/* -------------------------------------------------------------------------- */

/// @param size_t x
/// @param size_t y
typedef struct s_point
{
	size_t	x;
	size_t	y;
}			t_point;

/// @param size_t size_x
/// @param size_t size_y
/// @param int32_t colour
typedef struct s_minimap_element
{
	size_t	size_x;
	size_t	size_y;
	int32_t	colour;
}				t_minimap_element;

/// @param t_point start
/// @param t_point end
/// @param t_minimap_element element
/// @param int32_t colours[5]
typedef struct s_minimap
{
	t_point				start;
	t_point				end;
	t_minimap_element	element;
	int32_t				colours[5];
	size_t				offset;
}			t_minimap;

/* -------------------------------------------------------------------------- */
//								functions
/* -------------------------------------------------------------------------- */

// @note might not be needed
t_point	*point_get_new(int x, int y);
void	point_set(t_point *point, int x, int y);
void	debug_print_t_point(char *name, t_point point);

void	element_set(t_minimap_element *element, size_t size_x, size_t size_y);
void	element_set_colour(t_minimap *minimap, char symbol);
void	debug_print_t_element(char *name, t_minimap_element element);

void	minimap_init(t_minimap *minimap, size_t max_column, size_t max_line, 
			int mode);
void	minimap_draw(char **map, mlx_image_t *image, t_minimap minimap);
void	debug_print_t_minimap(char *name, t_minimap minimap);

#endif // MINIMAP_H
