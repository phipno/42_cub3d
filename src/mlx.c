/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 10:04:11 by pnolte            #+#    #+#             */
/*   Updated: 2023/06/26 19:29:26 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "minimap.h"
#include "cub3d.h"
#include "drawing.h"

#include <unistd.h>

void	game_update(t_all *all)
{
	if (all->image_game != NULL)
	{
		all->image_game->enabled = true;
		mlx_delete_image(all->mlx, all->image_game);
	}
	all->image_game = mlx_new_image(all->mlx, WIDTH, HEIGHT);
	if (all->image_game == NULL)
	{
		mlx_terminate(all->mlx);
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "image_game init");
	}
	draw_player(*all);
	if (mlx_image_to_window(all->mlx, all->image_game, 0, 0) == -1)
	{
		mlx_terminate(all->mlx);
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "image_game to window");
	}
}

void	image_init(t_all *cub, mlx_image_t **image)
{
	*image = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (*image == NULL)
	{
		mlx_terminate(cub->mlx);
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "image_background init");
	}
}

void	image_window(t_all *cub, mlx_image_t *image)
{
	if (mlx_image_to_window(cub->mlx, image, 0, 0) == -1)
	{
		mlx_terminate(cub->mlx);
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "image_game to window");
	}
}

void	init_mlx(t_all *all, char *argv[])
{
	all->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (all->mlx == NULL)
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "mlx init");
	cub_map_muncher(all, argv[1]);
	image_init(all, &all->image_background);
	image_init(all, &all->image_game);
	all->mode = MODE_OFF;
	all->per.offset.x = 0;
	all->per.offset.y = 0;
	minimap_update(all, all->mode);
	all->per.ms = MOVEMENT_SPEED;
}
