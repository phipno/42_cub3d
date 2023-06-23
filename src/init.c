/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:45:01 by pnolte            #+#    #+#             */
/*   Updated: 2023/06/23 09:52:33 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "cub3d.h"
#include "drawing.h"
#include "libft.h"
#include "MLX42.h"
#include "lm_str.h"
#include "lm_array_str.h"

static int	determine_file_size(char *file)
{
	int		fd;
	int		size;
	int		bytes_read;
	char	*buff;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		cub_exit(EXIT_FAILURE, STDERR_FILENO, strerror(1));
	size = 0;
	bytes_read = 1;
	buff = ft_calloc(1024, sizeof(char));
	if (buff == NULL)
		cub_exit(EXIT_FAILURE, STDERR_FILENO, strerror(1));
	while (bytes_read != 0)
	{
		bytes_read = read(fd, buff, 1024);
		if (bytes_read == -1)
			cub_exit(EXIT_FAILURE, STDERR_FILENO, strerror(1));
		size += bytes_read;
	}
	free(buff);
	close(fd);
	return (size);
}

static char	**get_file_content_split(int size, char *file)
{
	int		fd;
	char	*content;
	char	**content_split;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		cub_exit(EXIT_FAILURE, STDERR_FILENO, strerror(1));
	content = ft_calloc(size, sizeof(char));
	if (content == NULL)
		cub_exit(EXIT_FAILURE, STDERR_FILENO, strerror(1));
	if (read(fd, content, size) == -1)
		cub_exit(EXIT_FAILURE, STDERR_FILENO, strerror(1));
	content[size - 1] = '\0';
	content_split = ft_split(content, '\n');
	close(fd);
	free(content);
	return (content_split);
}

static void	freeee_walls(char **walls)
{
	free(walls[0]);
	free(walls[1]);
	free(walls[2]);
	free(walls[3]);
}

static void	variable_shall_be_declared(t_game *map, char **content_split)
{
	int	fail;

	fail = 0;
	while (content_split[fail] != NULL)
		fail++;
	if (fail < 9)
		cub_exit(EXIT_FAILURE, STDERR_FILENO,
			"Not enough Information given in .cub file");
	map->walls[0] = sub_str_walls(content_split[0]);
	map->walls[1] = sub_str_walls(content_split[1]);
	map->walls[2] = sub_str_walls(content_split[2]);
	map->walls[3] = sub_str_walls(content_split[3]);
	map->mlx_wall[0] = mlx_load_png(map->walls[0]);
	map->mlx_wall[1] = mlx_load_png(map->walls[1]);
	map->mlx_wall[2] = mlx_load_png(map->walls[2]);
	map->mlx_wall[3] = mlx_load_png(map->walls[3]);
	freeee_walls(map->walls);
	if (map->mlx_wall[0] == NULL || map->mlx_wall[1] == NULL
		|| map->mlx_wall[2] == NULL || map->mlx_wall[3] == NULL)
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "MLX load png Error");
	split_that_color(&map->floor_color, content_split[4]);
	split_that_color(&map->sky_color, content_split[5]);
}

void	cub_map_muncher(t_all *cub, char *file)
{
	char	**content_split;
	int		content_size;

	if (lm_str_check_viable_end(file, ".cub") != 1)
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "map: wrong file extension");
	content_size = determine_file_size(file);
	if (content_size == 0)
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "Map: File seems empty");
	content_split = get_file_content_split(content_size, file);
	variable_shall_be_declared(&cub->map, content_split);
	creation_of_map(&cub->map, content_split);
	parse_map(&cub->map, content_split);
	lm_array_str_free(content_split);
	get_player_start(cub);
	cub->per.pos.x = cub->per.start_pos.x;
	cub->per.pos.y = cub->per.start_pos.y;
	cub->per.mid_dir = cub->per.dir;
	if (map_valid_question_mark(cub) == EXIT_FAILURE)
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "Map didnt pass validation");
}

/* ************************************************************************** */
