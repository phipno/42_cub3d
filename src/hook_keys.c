/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:28:07 by jwillert          #+#    #+#             */
/*   Updated: 2023/06/26 21:15:51 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"  // needed for MACROS, mlx_*(), mlx_key_data_t
#include "cub3d.h"  // needed for t_all
#include "minimap.h"// needed for macros, t_minimap
#include "drawing.h"
#include <unistd.h> // needed for STDERR_FILENO
#include <math.h>   // needed for cos(), sin(), tan()
#include <stdio.h>  // needed for dprintf()

void	hook_keys(mlx_key_data_t key_data, void *context)
{
	t_all	*all;

	all = (t_all *) context;
	if (key_data.key == MLX_KEY_LEFT_SHIFT && key_data.action == MLX_PRESS)
	{
		all->per.ms += 0.05;
	}
	if (key_data.key == MLX_KEY_LEFT_SHIFT && key_data.action == MLX_RELEASE)
	{
		all->per.ms -= 0.05;
	}
	if (mlx_is_key_down(all->mlx, MLX_KEY_ESCAPE) == true)
	{
		mlx_close_window(all->mlx);
	}
	else if (key_data.key == MLX_KEY_M && key_data.action == MLX_PRESS)
	{
		minimap_toggle(all);
	}
}
