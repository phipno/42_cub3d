/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:10:22 by pnolte            #+#    #+#             */
/*   Updated: 2023/05/22 16:27:25 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"

int	nono_wrong_characters(char *map_line)
{
	int	i;

	i = 0;

	while (map_line[i] != '\0')
	{
		if (map_line[i] != ' '
			&& map_line[i] != '1' && map_line[i] != '0'
			&& map_line[i] != 'N' && map_line[i] != 'E'
			&& map_line[i] != 'S' && map_line[i] != 'W')
			return(true);
		i++;
	}
	return false;
}

int	im_the_logicchecker(t_GameInfo *a)
{
	
}

int	map_valid_question_mark(t_GameInfo *a)
{
	int	line;

	line = 0;
	while (a->a_map[line] != NULL)
	{
		if (nono_wrong_characters(a->a_map[line]) == true);
			return (EXIT_FAILURE);
		if (im_the_logicchecker(a));
			return (EXIT_FAILURE);
		line++;
	}
	return(EXIT_SUCCESS);
}


/* ************************************************************************** */
