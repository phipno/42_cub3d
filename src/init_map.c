/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:45:01 by pnolte            #+#    #+#             */
/*   Updated: 2023/05/22 16:09:49 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


#include "inc/cub3d.h"
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

int parse_map(t_GameInfo *map_info, char **da)
{
	size_t	line;
	size_t	collum;

	line = 0;
	while (da[line + 6] != NULL)
	{
		collum = 0;
		while (collum < map_info->map_collum_max)
		{
			if (collum >= ft_strlen(da[line + 6]))
				map_info->a_map[line][collum] = ' ';
			else
				map_info->a_map[line][collum] = da[line + 6][collum];
			collum++;
		}
		map_info->a_map[line][collum] = '\0';
		line++;
	}
	map_info->a_map[line] = NULL;
	return (EXIT_SUCCESS);
}

int	creation_of_map(t_GameInfo *map_info, char **da)
{
	map_info->map_collum_max = find_collum_max(da);
	map_info->map_line_max = find_line_max(da);
	printf("Collum_Max: %zu\nLine_Max: %zu\n", map_info->map_collum_max + 1, map_info->map_line_max);


	map_info->a_map = ft_calloc(map_info->map_line_max + 1, sizeof(char *));
	if (map_info->a_map == NULL)
	{
		perror("Malloc: ");
		return (EXIT_FAILURE);
	}

	size_t line = 0;
	while (line < map_info->map_line_max)
	{
		map_info->a_map[line] = ft_calloc(map_info->map_collum_max + 1, sizeof(char));
		if (map_info->a_map == NULL)
		{
			perror("Malloc: ");
			return (EXIT_FAILURE);
		}
		line++;
	}

	if (parse_map(map_info, da) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	for (int i = 0; map_info->a_map[i] != NULL; i++) {
		printf("%s\n", map_info->a_map[i]);
	}

	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
