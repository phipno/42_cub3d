/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:28:07 by jwillert          #+#    #+#             */
/*   Updated: 2023/05/24 12:32:57 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"	// needed for MACROS, mlx_*(), mlx_key_data_t
#include "cub3d.h"	// needed for t_all

void	hook_keys(mlx_key_data_t key_data, void *context)
{
	t_all *all;

	(void) key_data;
	all = (t_all *) context;
	if (mlx_is_key_down(all->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(all->mlx);
	}
}
