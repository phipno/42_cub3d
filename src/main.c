/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:15:21 by pnolte            #+#    #+#             */
/*   Updated: 2023/05/24 10:29:24 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>		// needed for MACROS
#include "MLX42.h"		// needed for MACROS
#include "libft.h"		// needed for ft_putstr_fd()
#include "cub3d.h"		// needed for t_all
#include "ft_printf.h"	// needed for ft_printf()

int	main(int argc, char *argv[])
{
	t_all all;
	int	status;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: \"./cub3D maps/<pick one>\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	status = cub_map_muncher(&all, argv[1]);
	ft_printf(STDERR_FILENO, "Exited with status: %d\n", status);
	return (status);
}

/* ************************************************************************** */
