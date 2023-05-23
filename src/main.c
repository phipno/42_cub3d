/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:15:21 by pnolte            #+#    #+#             */
/*   Updated: 2023/05/23 19:48:34 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//alle includes die der File braucht oben in den File

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "MLX42.h"
#include "libft.h"
#include "cub3d.h"
#include "ft_printf.h"

int	main(int argc, char *argv[]) {
	t_all all;
	int	status;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: \"./cub3D maps/<pick one>\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	status = cub_map_muncher(&all, argv[1]);
	ft_printf(2, "Exited with status: %d\n", status);
	return (status);
}

/* ************************************************************************** */
