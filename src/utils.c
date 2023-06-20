/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:27:10 by jwillert          #+#    #+#             */
/*   Updated: 2023/06/20 10:22:59 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// needed for size_t
#include <stdbool.h>

size_t	get_bigger_sizet(size_t x, size_t y)
{
	if (x < y)
		return (y);
	else
		return (x);
}

bool	is_player_pos(char symbol)
{
	if (symbol == 'N'
		|| symbol == 'W'
		|| symbol == 'E'
		|| symbol == 'S')
	{
		return (true);
	}
	return (false);
}

double	get_player_direction(char symbol)
{
	if (symbol == 'N')
		return ((double) 0);
	else if (symbol == 'W')
		return ((double) 270);
	else if (symbol == 'E')
		return ((double) 90);
	else if (symbol == 'S')
		return ((double) 180);
	return ((double) 0);
}
