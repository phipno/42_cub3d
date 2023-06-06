/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:50:39 by pnolte            #+#    #+#             */
/*   Updated: 2023/05/31 21:18:09 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

typedef struct s_raycasting
{
	float	dir;
	float	add;
	int		screen_y;
	float	cur_x;
	float	cur_y;
}	t_raycasting;


#endif

/* ************************************************************************** */
