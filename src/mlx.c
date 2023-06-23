/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 10:04:11 by pnolte            #+#    #+#             */
/*   Updated: 2023/06/23 10:47:51 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "minimap.h"
#include "cub3d.h"

#include <unistd.h>

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
	update_minimap(all, all->mode);
	all->per.ms = MOVEMENT_SPEED;
}
