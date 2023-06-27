/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 10:04:11 by pnolte            #+#    #+#             */
/*   Updated: 2023/06/27 08:47:13 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "minimap.h"
#include "cub3d.h"
#include "drawing.h"

#include <unistd.h>

void	cub_image_init(t_all *cub, mlx_image_t **image)
{
	*image = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (*image == NULL)
	{
		mlx_terminate(cub->mlx);
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "image_background init");
	}
}

void	cub_image_to_window(t_all *cub, mlx_image_t *image)
{
	if (mlx_image_to_window(cub->mlx, image, 0, 0) == -1)
	{
		mlx_terminate(cub->mlx);
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "image_game to window");
	}
}

void	cub_init_mlx(t_all *all, char *argv[])
{
	all->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (all->mlx == NULL)
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "mlx init");
	cub_map_muncher(all, argv[1]);
	cub_image_init(all, &all->image_background);
	cub_image_init(all, &all->image_game);
	all->mode = MODE_OFF;
	all->per.offset.x = 0;
	all->per.offset.y = 0;
	cub_update_minimap(all, all->mode);
	all->per.ms = MOVEMENT_SPEED;
}
