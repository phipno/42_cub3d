/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:45:01 by pnolte            #+#    #+#             */
/*   Updated: 2023/06/21 13:58:01 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <math.h>    //needed for cos

#include "cub3d.h"
#include "libft.h"
#include "MLX42.h"
#include "lm_str.h"

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
	//@note print statement here
	printf("Size:%d\n", size);
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
	content_split = ft_split(content, '\n');
	close(fd);
	free(content);
	return (content_split);
}

static void	variable_shall_be_declared (t_game *map, char **content_split)
{
	int fail;


	fail = 0;
	while (content_split[fail] != NULL)
		fail++;
	if (fail < 9)
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "Not enough Information given in .cub file");
	map->walls[0] = sub_str_walls(content_split[0]);
	map->walls[1] = sub_str_walls(content_split[1]);
	map->walls[2] = sub_str_walls(content_split[2]);
	map->walls[3] = sub_str_walls(content_split[3]);
	map->mlx_wall[0] = mlx_load_png(map->walls[0]);
	map->mlx_wall[1] = mlx_load_png(map->walls[1]);
	map->mlx_wall[2] = mlx_load_png(map->walls[2]);
	map->mlx_wall[3] = mlx_load_png(map->walls[3]);
	if (map->mlx_wall[0] == NULL || map->mlx_wall[1] == NULL ||
		map->mlx_wall[2] == NULL || map->mlx_wall[3] == NULL)
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "MLX load png Error");
	split_that_color(&map->floor_color, content_split[4]);
	split_that_color(&map->sky_color, content_split[5]);

	//@note print statement for walls and color
	printf("%s\n%s\n%s\n%s\n", map->walls[0], map->walls[1], map->walls[2], map->walls[3]);
	printf("%x %x %x  Alpha:%x\n", map->floor_color.rgba.r, map->floor_color.rgba.b, map->floor_color.rgba.g, map->sky_color.rgba.a);
	printf("%x %x %x  Alpha:%x\n", map->sky_color.rgba.r, map->sky_color.rgba.b, map->sky_color.rgba.g, map->sky_color.rgba.a);
	printf("%x\n", map->floor_color.colour);
	printf("%x\n", map->sky_color.colour);
}


//@note this function defenitly needs cutting
void	get_player_start(t_all *cub)
{
	int		x;
	int		y;
	bool	only_one;

	y = 0;
	only_one = false;
	while (cub->map.a_map[y] != NULL)
	{
		x = 0;
		while (cub->map.a_map[y][x] != '\0')
		{
			if (cub->map.a_map[y][x] == 'N' || cub->map.a_map[y][x] == 'E'
				|| cub->map.a_map[y][x] == 'S' || cub->map.a_map[y][x] == 'W')
			{
				if (only_one == true)
					cub_exit(EXIT_FAILURE, STDERR_FILENO, "Map: Too many spawns in map file");
				if (cub->map.a_map[y][x] == 'N')
					cub->per.direction = 270;
				if (cub->map.a_map[y][x] == 'E')
					cub->per.direction = 0;
				if (cub->map.a_map[y][x] == 'S')
					cub->per.direction = 90;
				if (cub->map.a_map[y][x] == 'W')
					cub->per.direction = 180;
				cub->per.start_pos.x = x + 0.5;
				cub->per.start_pos.y = y + 0.5;
				only_one = true;
			}
			x++;
		}
		y++;
	}
	if (only_one == false)
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "Map: No spawning point found");

	printf("PosX_Y: [%f] | [%f]\nDir: [%f]\n", cub->per.pos.x, cub->per.pos.y, cub->per.direction);
	printf("PoDX_Y: [%f] | [%f]\nDir: [%f]\n", cub->per.d_pos.x, cub->per.d_pos.y, cub->per.direction);
}

void	cub_map_muncher(t_all *cub, char *file)
{
	char	**content_split;

	if (lm_str_check_viable_end(file, ".cub") != 1)
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "map: wrong file extension");
	content_split = get_file_content_split(determine_file_size(file), file);
	// @note content_split print statement here
	for (int i = 0; content_split[i] != NULL; i++) {
		printf("%d. %s\n", i, content_split[i]);
	}
	variable_shall_be_declared(&cub->map, content_split);
	creation_of_map(&cub->map, content_split);
	parse_map(&cub->map, content_split);
	get_player_start(cub);
	cub->per.pos.x = cub->per.start_pos.x;
	cub->per.pos.y = cub->per.start_pos.y;
	if (map_valid_question_mark(cub) == EXIT_FAILURE)
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "Map didnt pass validation");
}

/* ************************************************************************** */
