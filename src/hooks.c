/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:28:07 by jwillert          #+#    #+#             */
/*   Updated: 2023/05/31 17:06:25 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"  // needed for MACROS, mlx_*(), mlx_key_data_t
#include "cub3d.h"  // needed for t_all

#include <unistd.h> // needed for STDERR_FILENO
#include <stdio.h>	// needed for printf() (DEBUGGING)

static void	handle_m(t_all *all)
{
	static unsigned int	i;

	i += 1;
//	printf("i_counter: %d\n", i);
	if (i == 1)	
	{
		mlx_delete_image(all->mlx, all->image_minimap);
		all->image_minimap = mlx_new_image(all->mlx, WIDTH, HEIGHT);
		if (all->image_minimap == NULL)
		{
			// @todo handle error
			mlx_terminate(all->mlx);
			cub_exit(EXIT_FAILURE, STDERR_FILENO, "image_minimap init");
		}
		minimap_init(all->minimap, all->map.map_column_max, all->map.map_line_max,
				MODE_CORNER);
		minimap_draw(all->map.a_map, all->image_minimap, *all->minimap);
	}
	else if (i == 2)
	{
		all->image_minimap->enabled = false;
	}
	else if (i == 3)
	{
		i = 0;
		mlx_delete_image(all->mlx, all->image_minimap);
		all->image_minimap = mlx_new_image(all->mlx, WIDTH, HEIGHT);
		if (all->image_minimap == NULL)
		{
			// @todo handle error
			mlx_terminate(all->mlx);
			cub_exit(EXIT_FAILURE, STDERR_FILENO, "image_minimap init");
		}
		all->image_minimap->enabled = true;
		minimap_init(all->minimap, all->map.map_column_max, all->map.map_line_max,
			MODE_FULLSCREEN);
		minimap_draw(all->map.a_map, all->image_minimap, *all->minimap);
	}
	if (i != 2)
	{
		if (mlx_image_to_window(all->mlx, all->image_minimap, 0, 0) == -1)
		{
			mlx_terminate(all->mlx);
			cub_exit(EXIT_FAILURE, STDERR_FILENO, "image_minimap to window");
		}
	}

}

void	hook_keys(mlx_key_data_t key_data, void *context)
{
	t_all	*all;

	(void) key_data;
	all = (t_all *) context;
	if (mlx_is_key_down(all->mlx, MLX_KEY_ESCAPE) == true)
	{
		mlx_close_window(all->mlx);
	}
	else if (mlx_is_key_down(all->mlx, MLX_KEY_M) == true)
	{
		handle_m(all);
	}
}
