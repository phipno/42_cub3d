/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:45:01 by pnolte            #+#    #+#             */
/*   Updated: 2023/05/25 19:12:51 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

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
	sub_str_walls(&map->north_wall, content_split[0]);
	sub_str_walls(&map->east_wall, content_split[1]);
	sub_str_walls(&map->south_wall, content_split[2]);
	sub_str_walls(&map->west_wall, content_split[3]);
	split_that_color(&map->floor_color, content_split[4]);
	split_that_color(&map->sky_color, content_split[5]);

	//@note print statement for walls and color
	printf("%s\n%s\n%s\n%s\n", map->north_wall, map->east_wall, map->south_wall, map->west_wall);
	printf("%x %x %x  Alpha:%d\n", map->floor_color.rgba.r, map->floor_color.rgba.b, map->floor_color.rgba.g, map->sky_color.rgba.a);
	printf("%d %x %x  Alpha:%d\n", map->sky_color.rgba.r, map->sky_color.rgba.b, map->sky_color.rgba.g, map->sky_color.rgba.a);
	printf("%x\n", map->sky_color.colour);
	printf("%x\n", map->floor_color.colour);

}

void	cub_map_muncher(t_all *cub, char *file)
{
	char	**content_split;

	if (lm_str_check_viable_end(file, ".cub") != 1)
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "map: wrong file extension");
	content_split = get_file_content_split(determine_file_size(file), file);
	//@note content_split print statement here
	// for (int i = 0; content_split[i] != NULL; i++) {
	// 	printf("%d. %s\n", i, content_split[i]);
	// }

	//parsing into each variable
	variable_shall_be_declared(&cub->map, content_split);
	creation_of_map(&cub->map, content_split);
	parse_map(&cub->map, content_split);
	if (map_valid_question_mark(&cub->map) == EXIT_FAILURE)
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "Map didnt pass validation");
}

/* ************************************************************************** */
