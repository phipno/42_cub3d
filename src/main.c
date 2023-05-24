/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:15:21 by pnolte            #+#    #+#             */
/*   Updated: 2023/05/24 12:34:11 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>		// needed for MACROS
#include "MLX42.h"		// needed for MACROS
#include "libft.h"		// needed for ft_putstr_fd()
#include "cub3d.h"		// needed for t_all
#include "ft_printf.h"	// needed for ft_printf()

int	main(int argc, char *argv[])
{
	t_all	all;
	int		status;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: \"./cub3D maps/<pick one>\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}

	// parsing
	status = cub_map_muncher(&all, argv[1]);


	// mlx init
	all.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (all.mlx == NULL)
	{
		ft_putstr_fd("Error: mlx init\n", 2);
	}

	// main program

	mlx_key_hook(all.mlx, &hook_keys, &all);
	mlx_loop(all.mlx);




	// cleaning up
	mlx_terminate(all.mlx);
	ft_printf(STDERR_FILENO, "Exited with status: %d\n", status);
	return (status);
}

/* ************************************************************************** */
