/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:15:21 by pnolte            #+#    #+#             */
/*   Updated: 2023/06/26 19:32:34 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"		// needed for t_all
#include "minimap.h"	// needed for t_minimap
#include "drawing.h"

#include "MLX42.h"		// needed for MACROS, mlx_*
#include "libft.h"		// needed for ft_putstr_fd(), ft_putendl_fd()
#include "ft_printf.h"	// needed for ft_printf()
#include "lm_array_str.h"

#include <stdio.h>
#include <unistd.h>		// needed for MACROS
#include <math.h>

int	main(int argc, char *argv[])
{
	t_all		all;
	int			status;

	status = EXIT_SUCCESS;
	if (argc != 2)
		cub_exit(EXIT_FAILURE, STDERR_FILENO,
			"Usage: \"./cub3D maps/<pick one>");
	init_mlx(&all, argv);
	draw_heaven_and_hell(all);
	image_window(&all, all.image_background);
	draw_player(all);
	image_window(&all, all.image_game);
	mlx_key_hook(all.mlx, &hook_keys, &all);
	mlx_loop_hook(all.mlx, &hook_frame, &all);
	mlx_loop(all.mlx);
	mlx_terminate(all.mlx);
	freeee(&all);
	ft_printf(STDERR_FILENO, "Exited with status: %d\n", status);
	return (status);
}

/* ************************************************************************** */
