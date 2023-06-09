/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:15:21 by pnolte            #+#    #+#             */
/*   Updated: 2023/06/09 15:07:50 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>		// needed for MACROS
#include "MLX42.h"		// needed for MACROS, mlx_*
#include "libft.h"		// needed for ft_putstr_fd(), ft_putendl_fd()
#include "cub3d.h"		// needed for t_all
#include "minimap.h"	// needed for t_minimap
#include "ft_printf.h"	// needed for ft_printf()

#include "stdio.h"
#include <math.h>

void	cub_exit(int exit_code, int fd, char *message)
{
	ft_putstr_fd("Error: ", fd);
	ft_putendl_fd(message, fd);
	exit(exit_code);
}

int	main(int argc, char *argv[])
{
	t_all		all;
	int			status;

	status = EXIT_SUCCESS;
	if (argc != 2)
	{
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "Usage: \"./cub3D maps/<pick one>");
	}

	//	--------------------->	parsing

	cub_map_muncher(&all, argv[1]);

	if (PARSING_TESTER)
	{
		return (EXIT_SUCCESS);
	}

	// mlx init
	all.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (all.mlx == NULL)
	{
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "mlx init");
	}

	//	--------------------->	image_game

	all.image_game = mlx_new_image(all.mlx, WIDTH, HEIGHT);
	if (all.image_game == NULL)
	{
		mlx_terminate(all.mlx);
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "image_game init");
	}

	draw_heaven_and_hell(all);
	// draw_troll(all);

	if (mlx_image_to_window(all.mlx, all.image_game, 0, 0) == -1)
	{
		mlx_terminate(all.mlx);
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "image_game to window");
	}

	// //	--------------------->	image_minimap

	all.image_minimap = NULL;
	all.mode = MODE_FULLSCREEN;
	update_minimap(&all, MODE_FULLSCREEN);

	//	--------------------->	image_player
	all.per.angle_real = 0;
	all.per.offset.x = 0;
	all.per.offset.y = 0;
	all.image_player = NULL;
	update_player_pos(&all);
	draw_player(all);

	//	--------------------->	keys and loop

	all.ms = MOVEMENT_SPEED;
	mlx_key_hook(all.mlx, &hook_keys, &all);
	mlx_loop_hook(all.mlx, &hook_frame, &all);
	mlx_loop(all.mlx);

	// clean up
	mlx_terminate(all.mlx);
	ft_printf(STDERR_FILENO, "Exited with status: %d\n", status);
	return (status);
}

/* ************************************************************************** */
