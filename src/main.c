/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:15:21 by pnolte            #+#    #+#             */
/*   Updated: 2023/06/22 17:38:28 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"		// needed for t_all
#include "minimap.h"	// needed for t_minimap
#include "drawing.h"

#include "MLX42.h"		// needed for MACROS, mlx_*
#include "libft.h"		// needed for ft_putstr_fd(), ft_putendl_fd()
#include "ft_printf.h"	// needed for ft_printf()

#include <stdio.h>
#include <unistd.h>		// needed for MACROS
#include <math.h>

void	cub_exit(int exit_code, int fd, char *message)
{
	ft_putstr_fd("Error: ", fd);
	ft_putendl_fd(message, fd);
	exit(exit_code);
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

void	init_shit(t_all *all, char *argv[])
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
	all->ms = MOVEMENT_SPEED;
}

int	main(int argc, char *argv[])
{
	t_all		all;
	int			status;

	status = EXIT_SUCCESS;
	if (argc != 2)
		cub_exit(EXIT_FAILURE, STDERR_FILENO,
			"Usage: \"./cub3D maps/<pick one>");
	init_shit(&all, argv);
	draw_heaven_and_hell(all);
	image_window(&all, all.image_background);
	draw_player(all);
	image_window(&all, all.image_game);
	mlx_key_hook(all.mlx, &hook_keys, &all);
	mlx_loop_hook(all.mlx, &hook_frame, &all);
	mlx_loop(all.mlx);
	mlx_terminate(all.mlx);
	ft_printf(STDERR_FILENO, "Exited with status: %d\n", status);
	return (status);
}

/* ************************************************************************** */
