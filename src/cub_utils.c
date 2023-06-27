/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:27:10 by jwillert          #+#    #+#             */
/*   Updated: 2023/06/27 09:00:00 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"	// needed for size_t, cub_exit()
#include <unistd.h> // needed for STDERR_FILENO

size_t	cub_get_bigger_sizet(size_t x, size_t y)
{
	if (x < y)
		return (y);
	else
		return (x);
}

int	cub_get_rgba(int r, int g, int b, int a)
{
	if ((r > 255 || r < 0) || (g > 255 || g < 0) || (b > 255 || b < 0))
		cub_exit(EXIT_FAILURE, STDERR_FILENO,
			"Map: Color should only be in range of 0-255");
	return (r << 24 | g << 16 | b << 8 | a);
}
