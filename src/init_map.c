/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:45:01 by pnolte            #+#    #+#             */
/*   Updated: 2023/06/22 17:41:26 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "cub3d.h"
#include "libft.h"

size_t	find_column_max(char **da)
{
	int	max_column;
	int	current;
	int	line;

	line = 6;
	max_column = 0;
	while (da[line] != NULL)
	{
		current = 0;
		while (da[line][current] != '\0')
			current++;
		if (current > max_column)
			max_column = current;
		line++;
	}
	return (max_column);
}

size_t	find_line_max(char **da)
{
	int	max_line;

	max_line = 0;
	while (da[max_line] != NULL)
		max_line++;
	return (max_line - 6);
}

void	creation_of_map(t_game *map, char **content_split)
{
	size_t	line;

	line = 0;
	map->map_column_max = find_column_max(content_split);
	map->map_line_max = find_line_max(content_split);
	map->a_map = ft_calloc(map->map_line_max + 1, sizeof(char *));
	if (map->a_map == NULL)
		cub_exit(EXIT_FAILURE, STDERR_FILENO, strerror(1));
	while (line < map->map_line_max)
	{
		map->a_map[line] = ft_calloc(map->map_column_max + 1, sizeof(char));
		if (map->a_map == NULL)
			cub_exit(EXIT_FAILURE, STDERR_FILENO, strerror(1));
		line++;
	}
}

void	parse_map(t_game *map, char **content_split)
{
	size_t	line;
	size_t	column;

	line = 0;
	while (content_split[line + 6] != NULL)
	{
		column = 0;
		while (column < map->map_column_max)
		{
			if (column >= ft_strlen(content_split[line + 6]))
				map->a_map[line][column] = ' ';
			else
				map->a_map[line][column] = content_split[line + 6][column];
			column++;
		}
		map->a_map[line][column] = '\0';
		line++;
	}
	map->a_map[line] = NULL;
}

/* ************************************************************************** */
