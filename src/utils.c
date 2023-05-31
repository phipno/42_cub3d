/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:27:10 by jwillert          #+#    #+#             */
/*   Updated: 2023/05/31 11:01:28 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// needed for size_t

size_t	get_bigger_sizet(size_t x, size_t y)
{
	if (x < y)
		return (y);
	else
		return (x);
}
