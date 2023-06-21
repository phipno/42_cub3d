/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:10:22 by pnolte            #+#    #+#             */
/*   Updated: 2023/06/21 13:04:14 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include <stdio.h>
#include "cub3d.h"

int	im_the_logicchecker(t_game *a, size_t line)
{
	size_t i;

	i = 0;
	while (a->a_map[line][i] != '\0')
	{
		if (a->a_map[line][i] == '0' || a->a_map[line][i] == 'N'
			|| a->a_map[line][i] == 'E' || a->a_map[line][i] == 'S'
			|| a->a_map[line][i] == 'W')
		{
			if (line == 0 || line == a->map_line_max)
				return (true);
			if (i == 0 || i == a->map_column_max)
				return (true);
			if (a->a_map[line][i - 1] == ' ' ||  a->a_map[line][i + 1] == ' '
				|| a->a_map[line + 1][i] == ' ' || a->a_map[line - 1][i]== ' ')
				return (true);
		}
		i++;
	}
	return (false);
}

int	nono_wrong_characters(char *map_line)
{
	size_t	i;

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
	return (false);
}

int	map_valid_question_mark(t_game *a)
{
	size_t	line;

	line = 0;
	while (a->a_map[line] != NULL)
	{
		if (nono_wrong_characters(a->a_map[line]) == true)
		{
			printf("hello\n");
			return (EXIT_FAILURE);
		}
		if (im_the_logicchecker(a, line) == true)
		{
			printf("hi\n");
			return (EXIT_FAILURE);
		}
		line++;
	}
	return(EXIT_SUCCESS);
}


/* ************************************************************************** */
