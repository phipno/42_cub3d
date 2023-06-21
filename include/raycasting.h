/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:50:39 by pnolte            #+#    #+#             */
/*   Updated: 2023/06/21 16:56:15 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

#include "minimap.h" //for t_point

typedef struct s_raycaster
{
	double	x;
	double	y;
	t_point	map;
	t_point	offset;
	double	dir;
	int		cardinal_dir;
	double	distance_raw;
	double	distance_parralel;
	int32_t	color;
}	t_raycaster;


#endif

/* ************************************************************************** */
