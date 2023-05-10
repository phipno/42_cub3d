/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:45:01 by pnolte            #+#    #+#             */
/*   Updated: 2023/05/10 16:07:41 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "inc/cub3d.h"
#include "lib/MLX42/include/MLX42/MLX42.h"

int	cub_map_muncher(t_all a, char *argv[])
{
	int fd;

	fd = open(argv[1], O_RDONLY);
	//not sure about that 2
	if (fd < 2)
	{

		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
