/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:10:22 by pnolte            #+#    #+#             */
/*   Updated: 2023/05/23 17:51:35 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"

int	im_the_logicchecker(t_GameInfo *a, int line)
{
	int i;

	i = 0;
	while (a->a_map[line][i] != '\0')
	{
		if (a->a_map[line][i] == '0' && a->a_map[line][i] == 'N'
			&& a->a_map[line][i] == 'E' && a->a_map[line][i] == 'S'
			&& a->a_map[line][i] == 'W')
		{
			if (line == 0 || line == a->map_line_max)
				return (true);
			if (i == 0 || i == a->map_collum_max)
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
	return (false);
}

// void	move_y(int dir, t_GameInfo *a, int *y, int *x)
// {
// 	while (a->a_map[*y][*x] != ' ' && a->a_map[*y] != NULL)
// 		*y += dir;
// }

// void	move_x(int dir, t_GameInfo *a, int *y, int *x)
// {
// 	while (a->a_map[*y][*x] != ' ' && a->a_map[*y][*x] != '\0')
// 		*x += dir;
// }


int	is_map_open(t_GameInfo *a)
{
	int x;
	int y;
	int x_start;
	bool	rotation_complete;

	rotation_complete = false;

	y = 0;
	x = 0;
	while (a->a_map[y][x] != 1)
		x++;
	x_start = x;
	while (rotation_complete != true)
	{
		while(a->a_map[y][x] != ' ')
			x++
		if ()

		if ()

		while (a->a_map[y][x] != ' ' && a->a_map[y] != NULL)
			y++;
	}

	return (false);
}

int	map_valid_question_mark(t_GameInfo *a)
{
	int	line;

	line = 0;
	while (a->a_map[line] != NULL)
	{
		if (nono_wrong_characters(a->a_map[line]) == true);
			return (EXIT_FAILURE);
		if (im_the_logicchecker(a, line));
			return (EXIT_FAILURE);
		line++;
	}
	if (is_map_open(a) == true)
		return(true);
	return(EXIT_SUCCESS);
}


/* ************************************************************************** */
