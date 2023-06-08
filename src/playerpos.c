/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerpos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert@student.42heilbronn.de            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:22:19 by jwillert          #+#    #+#             */
/*   Updated: 2023/06/08 13:15:35 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"   // needed for t_player, t_minimap
#include "minimap.h" // needed for point_*()

void	player_set_pos(t_player *per, int x, int y)
{
	per->pos_x = x;
	per->pos_y = y;
}
