/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:15:21 by pnolte            #+#    #+#             */
/*   Updated: 2023/05/12 13:55:49 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//alle includes die der File braucht oben in den File

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "inc/cub3d.h"
#include "lib/libft-phipno/libft.h"
#include "lib/MLX42/include/MLX42/MLX42.h"

int	main(int argc, char *argv[]) {
	t_all all;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: \"./cub3D maps/<pick one>\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	cub_map_muncher(&all, argv);
}



/* ************************************************************************** */
