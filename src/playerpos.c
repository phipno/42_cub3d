/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerpos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:22:19 by jwillert          #+#    #+#             */
/*   Updated: 2023/06/20 10:54:30 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"   // needed for t_player, t_minimap
#include "minimap.h" // needed for point_*()
#include <stdio.h>

void	player_set_pos(t_player *per, int x, int y)
{
	per->pos.x = x;
	per->pos.y = y;
}

void	get_player_pos(char **map, t_all *all)
{
	size_t	index_x;
	size_t	index_y;
	
	index_x = 0;
	index_y = 0;
	while (map[index_y] != NULL && index_y < all->map.map_line_max)
	{
		while (map[index_y][index_x] != '\0' && index_x < all->map.map_column_max)
		{
			if (is_player_pos(map[index_y][index_x]) == true)
			{
				all->player_pos.index_x = index_x;
				all->player_pos.index_y = index_y;
				all->player_pos.symbol = map[index_y][index_x];
				all->player_pos.direction = get_player_direction(map[index_y][index_x]);
				break ;
			}
			index_x += 1;
		}
		index_x = 0;
		index_y += 1;
	}
}
