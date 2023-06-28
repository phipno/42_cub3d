/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:15:21 by pnolte            #+#    #+#             */
/*   Updated: 2023/06/28 07:54:42 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"   // needed for t_all, MLX42.h, cub_*()
#include "drawing.h" // needed for draw_*()
#include <unistd.h>  // needed for MACROS

int	main(int argc, char *argv[])
{
	t_all	all;

	if (argc != 2)
		cub_exit(EXIT_FAILURE, STDERR_FILENO,
			"Usage: \"./cub3D maps/<pick one>");
	cub_init_mlx_and_map(&all, argv);
	draw_heaven_and_hell(all);
	cub_image_to_window(&all, all.image_background);
	draw_player(all);
	cub_image_to_window(&all, all.image_game);
	mlx_key_hook(all.mlx, &cub_hook_keys, &all);
	mlx_loop_hook(all.mlx, &cub_hook_frame, &all);
	mlx_loop(all.mlx);
	mlx_terminate(all.mlx);
	cub_freeee(&all);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
