/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_minimap.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert@student.42heilbronn.de            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:45:22 by jwillert          #+#    #+#             */
/*   Updated: 2023/05/25 20:45:11 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_MINIMAP_H
# define CUB_MINIMAP_H

#define DEBUG_FD 2

typedef struct s_vec_pos
{
	int	x;
	int	y;
}				t_vec_pos;

typedef struct s_minimap
{
	t_vec_pos	start;
	t_vec_pos	end;
	int			scale_x;
	int			scale_y;
}				t_minimap;

void	vec_pos_print(int fd, char *name, t_vec_pos *vec);
void	minimap_print(int fd, t_minimap *mini);

int		minimap_init(t_minimap *minimap, t_vec_pos start, t_vec_pos end);
int		minimap_draw(mlx_image_t *image, t_vec_pos *start, t_vec_pos *end);

#endif // CUB_MINIMAP_H
