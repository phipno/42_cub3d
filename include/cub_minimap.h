/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_minimap.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:45:22 by jwillert          #+#    #+#             */
/*   Updated: 2023/05/30 15:21:12 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_MINIMAP_H
# define CUB_MINIMAP_H

#define START_X 0
#define START_Y 0
#define END_X 300
#define END_Y 300

#define COLOUR_FLOOR 	0xFFa
#define COLOUR_WALL		0xFFFFF
#define COLOUR_PLAYER 	0xFFF
#define COLOUR_EMPTY 	0x808080
#define COLOUR_NOTFOUND 0xFFFF0F

#include "MLX42.h"	// needed for mlx_image_t
#include <stdlib.h>	// needed for size_t
#include "cub3d.h"	// needed for t_game

typedef struct s_point
{
	size_t	x;
	size_t	y;
}			t_point;

t_point	*point_get_new(int x, int y);
void	point_set(t_point *point, int x, int y);
void	debug_print_t_point(char *name, t_point point);

typedef struct	s_minimap_element
{
	size_t	size_x;
	size_t	size_y;
	int		colour;
}				t_minimap_element;

void	element_set(t_minimap_element *element, size_t size_x, size_t size_y);
void	element_set_colour(t_minimap_element *element, char symbol);
void	debug_print_t_element(char *name, t_minimap_element element);

typedef struct	s_minimap
{
	t_point				start;
	t_point				end;
	t_minimap_element	element;
}			t_minimap;

void	minimap_init(t_minimap *minimap, t_game game);
int		minimap_draw(char **map, mlx_image_t *image, t_minimap minimap);
void	debug_print_t_minimap(char *name, t_minimap minimap);

#endif // CUB_MINIMAP_H
