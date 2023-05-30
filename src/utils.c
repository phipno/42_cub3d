/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert@student.42heilbronn.de            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:27:10 by jwillert          #+#    #+#             */
/*   Updated: 2023/05/30 14:28:04 by jwillert         ###   ########          */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// needed for size_t

size_t	return_bigger(size_t x, size_t y)
{
	if (x < y)
		return (y);
	else
		return (x);
}
