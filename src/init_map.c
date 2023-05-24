/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:45:01 by pnolte            #+#    #+#             */
/*   Updated: 2023/05/24 15:23:37 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "cub3d.h"
#include "libft.h"

size_t	find_collum_max(char **da)
{
	int max_collum;
	int current;
	int line;

	line = 6;
	max_collum = 0;
	while (da[line] != NULL)
	{
		current = 0;
		while (da[line][current] != '\0')
			current++;
		if (current > max_collum)
			max_collum = current;
		line++;
	}
	return (max_collum);
}

size_t	find_line_max(char **da)
{
	int max_line;

	max_line = 0;
	while (da[max_line] != NULL)
		max_line++;
	//the - 6 because a valid map in the char **da should begin at line 6
	//some hard code :D
	return (max_line - 6);
}


void	creation_of_map(t_game *map, char **content_split)
{
	map->map_collum_max = find_collum_max(content_split);
	map->map_line_max = find_line_max(content_split);
	//@note print statement for **map sizes
	// printf("Collum_Max: %zu\nLine_Max: %zu\n", map->map_collum_max + 1, map->map_line_max);
	map->a_map = ft_calloc(map->map_line_max + 1, sizeof(char *));
	if (map->a_map == NULL)
		cub_exit(EXIT_FAILURE, STDERR_FILENO, strerror(1));
	size_t line = 0;
	while (line < map->map_line_max)
	{
		map->a_map[line] = ft_calloc(map->map_collum_max + 1, sizeof(char));
		if (map->a_map == NULL)
			cub_exit(EXIT_FAILURE, STDERR_FILENO, strerror(1));
		line++;
	}
}

void	parse_map(t_game *map, char **content_split)
{
	size_t	line;
	size_t	collum;

	line = 0;
	while (content_split[line + 6] != NULL)
	{
		collum = 0;
		while (collum < map->map_collum_max)
		{
			if (collum >= ft_strlen(content_split[line + 6]))
				map->a_map[line][collum] = ' ';
			else
				map->a_map[line][collum] = content_split[line + 6][collum];
			collum++;
		}
		map->a_map[line][collum] = '\0';
		line++;
	}
	map->a_map[line] = NULL;
	// @note print statement for the **map
	for (int i = 0; map->a_map[i] != NULL; i++) {
		printf("%s\n", map->a_map[i]);
	}
}

/* ************************************************************************** */
