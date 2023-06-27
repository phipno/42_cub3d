/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 10:05:58 by pnolte            #+#    #+#             */
/*   Updated: 2023/06/27 08:26:58 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "MLX42.h"
#include "libft.h"
#include "lm_array_str.h"

void	cub_freeee(t_all *cub)
{
	lm_array_str_free(cub->map.a_map);
	mlx_delete_texture(cub->map.mlx_wall[NORTH]);
	mlx_delete_texture(cub->map.mlx_wall[EAST]);
	mlx_delete_texture(cub->map.mlx_wall[SOUTH]);
	mlx_delete_texture(cub->map.mlx_wall[WEST]);
}

void	cub_exit(int exit_code, int fd, char *message)
{
	ft_putstr_fd("Error: ", fd);
	ft_putendl_fd(message, fd);
	exit(exit_code);
}
