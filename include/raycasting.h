/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:50:39 by pnolte            #+#    #+#             */
/*   Updated: 2023/06/09 21:28:29 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

typedef struct s_raycaster
{
	double	x;
	double	y;
	double	dir;
	double	x_offset;
	double	y_offset;
	double	distance_per;
}	t_raycaster;


#endif

/* ************************************************************************** */
