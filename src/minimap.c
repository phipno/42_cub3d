/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert@student.42heilbronn.de            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:49:37 by jwillert          #+#    #+#             */
/*   Updated: 2023/05/25 21:00:58 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"			// needed for mlx_*()
#include "cub_minimap.h"	// needed for t_vec_pos
#include "cub3d.h"			// needed for t_all
#include "ft_printf.h"		// needed for ft_printf()

void	vec_pos_print(int fd, char *name, t_vec_pos *vec)
{
	ft_printf(fd, "______________________\n");
	ft_printf(fd, "t_vec_pos: %s\n", name);
	ft_printf(fd, "           %p\n", vec);
	ft_printf(fd, "           |x %d|\n", vec->x);
	ft_printf(fd, "           |y %d|\n", vec->y);
	ft_printf(fd, "______________________\n");
}

void	minimap_print(int fd, t_minimap *mini)
{
	ft_printf(fd, "______________________\n");
	ft_printf(fd, "t_minimap:\n");
	ft_printf(fd, "           %p\n", mini);
	ft_printf(fd, "______________________\n");
}

int	minimap_init(t_minimap *minimap, t_vec_pos start, t_vec_pos end)
{
	minimap->start = start;
	minimap->end = end;

	//get the scale depending on the distance between start and end
	minimap->scale_x = (minimap->start.y) - (minimap->end.y);
	minimap->scale_y = (minimap->start.x) - (minimap->end.x);

	ft_printf(2, "scale_y = %d\n", minimap->scale_x);
	ft_printf(2, "scale_x = %d\n", minimap->scale_y);

	return (EXIT_SUCCESS);
}

int	minimap_draw(mlx_image_t *image, t_vec_pos *start, t_vec_pos *end)
{
	//loop through pixels until you hit end position
	int x;
	int y;
	
	x = start->x;
	y = start->y;
	while (y < end->y && y < HEIGHT)
	{
		while (x < end->x && x < WIDTH)
		{
			mlx_put_pixel(image, x, y, 0xFF);
			x += 1;
			ft_printf(DEBUG_FD, "x = %d\n", x);
		}
		x = start->x;
		y += 1;
		ft_printf(DEBUG_FD, "y = %d\n", y);
	}
	return (EXIT_SUCCESS);
}
