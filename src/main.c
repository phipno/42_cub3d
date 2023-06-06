/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:15:21 by pnolte            #+#    #+#             */
/*   Updated: 2023/06/06 15:17:25 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>		// needed for MACROS
#include "MLX42.h"		// needed for MACROS, mlx_*
#include "libft.h"		// needed for ft_putstr_fd(), ft_putendl_fd()
#include "cub3d.h"		// needed for t_all
#include "minimap.h"	// needed for t_minimap
#include "ft_printf.h"	// needed for ft_printf()

void	cub_exit(int exit_code, int fd, char *message)
{
	ft_putstr_fd("Error: ", fd);
	ft_putendl_fd(message, fd);
	exit(exit_code);
}

int	main(int argc, char *argv[])
{
	t_all		all;
	t_minimap	minimap;
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
	draw_troll(all);

	if (mlx_image_to_window(all.mlx, all.image_game, 0, 0) == -1)
	{
		mlx_terminate(all.mlx);
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "image_game to window");
	}

	//	--------------------->	image_minimap

	all.image_minimap = mlx_new_image(all.mlx, WIDTH, HEIGHT);
	if (all.image_minimap == NULL)
	{
		mlx_terminate(all.mlx);
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "image_minimap init");
	}

	all.minimap = &minimap;
	minimap_init(&minimap, all.map.map_column_max, all.map.map_line_max,
			MODE_FULLSCREEN);
	minimap_draw(all.map.a_map, all.image_minimap, &minimap);
	if (mlx_image_to_window(all.mlx, all.image_minimap, 0, 0) == -1)
	{
		mlx_terminate(all.mlx);
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "image_minimap to window");
	}

	//	--------------------->	keys and loop

	mlx_key_hook(all.mlx, &hook_keys, &all);
	mlx_loop(all.mlx);

	// clean up
	mlx_terminate(all.mlx);
	ft_printf(STDERR_FILENO, "Exited with status: %d\n", status);
	return (status);
}

/* ************************************************************************** */
