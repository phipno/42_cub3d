/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:50:39 by pnolte            #+#    #+#             */
/*   Updated: 2023/06/19 15:49:00 by pnolte           ###   ########.fr       */
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
	int		cardinal_dir;
	double	distance_raw;
	double	distance_parralel;
	int32_t	color;
}	t_raycaster;


#endif

/* ************************************************************************** */
