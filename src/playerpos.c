/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerpos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:22:19 by jwillert          #+#    #+#             */
/*   Updated: 2023/06/08 17:26:26 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"   // needed for t_player, t_minimap
#include "minimap.h" // needed for point_*()

void	player_set_pos(t_player *per, int x, int y)
{
	per->pos.x = x;
	per->pos.y = y;
}
