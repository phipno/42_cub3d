/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_hook_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:28:07 by jwillert          #+#    #+#             */
/*   Updated: 2023/06/27 08:58:59 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h" // needed for t_all, MLX42.h, MACROS, size_t

static void	toggle_minimap(t_all *all)
{
	static size_t	i;

	i += 1;
	if (i == 1)
	{
		all->mode = MODE_FULLSCREEN;
	}
	else if (i == 2)
	{
		all->mode = MODE_CORNER;
	}
	else if (i == 3)
	{
		all->mode = MODE_OFF;
		i = 0;
	}
	cub_update_game(all);
	cub_update_minimap(all, all->mode);
}


void	cub_hook_keys(mlx_key_data_t key_data, void *context)
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
		toggle_minimap(all);
	}
}
