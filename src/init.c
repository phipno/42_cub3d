/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:45:01 by pnolte            #+#    #+#             */
/*   Updated: 2023/05/23 19:57:48 by jwillert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include "cub3d.h"
#include "libft.h"
#include "MLX42.h"

int	sub_str_walls(char **write_to, const char *str)
{
	int		i;
	int		fd;

	i = 0;
	//this while condition needs more defining
	while (str[i] != '.' && str[i] != '\0')
		i++;
	*write_to = ft_substr(str, i, ft_strlen(str));
	fd = open(*write_to, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Open Error \"", 2);
		ft_putstr_fd((char *)str, 2);
		ft_putstr_fd("\" : ", 2);
		perror("");
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	split_that_color(int write_to[3], const char *str)
{
	int		i;
	char	*sub;
	char	**split;

	i = 0;
	while (ft_isdigit(str[i]) == 0 && str[i] != '\0')
		i++;
	sub = ft_substr(str, i, ft_strlen(str));
	split = ft_split(sub, ',');
	i = 0;
	while (i < 3 && split[i] != NULL) {
		write_to[i] = ft_atoi(split[i]);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if (write_to[i] > 255 || write_to[i] < 0)
		{
			ft_putstr_fd("Color Error: \"", 2);
			ft_putstr_fd((char *)str, 2);
			ft_putstr_fd("\"\n", 2);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int		cub_map_muncher(t_all *cub, char *file)
{
	int		fd;
	int		bytes_read;
	int		size;
	char	*content;
	char	*buff;

	fd = open(file, O_RDONLY);
	//not sure about that 2
	if (fd < 0)
	{
		perror("Open: ");
		return (EXIT_FAILURE);
	}
	size = 0;
	bytes_read = 1;
	buff = ft_calloc(1024, sizeof(char));
	if (buff == NULL)
	{
		perror("Malloc: ");
		return EXIT_FAILURE;
	}
	while (bytes_read != 0)
	{
		bytes_read = read(fd, buff, 1024);
		if (bytes_read == -1)
		{
			perror("Read: ");
			return (EXIT_FAILURE);
		}
		size += bytes_read;
	}
	printf("Size:%d\n", size);
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Open: ");
		return (EXIT_FAILURE);
	}
	content = ft_calloc(size, sizeof(char));
	if (buff == NULL)
	{
		perror("Malloc: ");
		return EXIT_FAILURE;
	}
	if (read(fd, content, size) == -1)
	{
		perror("Read: ");
		return (EXIT_FAILURE);
	}

	char **da;

	da = ft_split(content, '\n');
	for (int i = 0; da[i] != NULL; i++) {
		printf("%d. %s\n", i, da[i]);
	}

	//parsing into each variable

	int fail;

	fail = sub_str_walls(&cub->map.north_wall, da[0]);
	fail = sub_str_walls(&cub->map.east_wall, da[1]);
	fail = sub_str_walls(&cub->map.south_wall, da[2]);
	fail = sub_str_walls(&cub->map.west_wall, da[3]);

	printf("%s\n%s\n%s\n%s\n", cub->map.north_wall, cub->map.east_wall, cub->map.south_wall, cub->map.west_wall);

	fail = split_that_color(cub->map.floor_color, da[4]);
	fail = split_that_color(cub->map.sky_color, da[5]);

	printf("%d %d %d\n", cub->map.floor_color[0], cub->map.floor_color[1], cub->map.floor_color[2]);
	printf("%d %d %d\n", cub->map.sky_color[0], cub->map.sky_color[1], cub->map.sky_color[2]);

	if (fail == EXIT_FAILURE)
		return (EXIT_FAILURE);

	if (creation_of_map(&cub->map, da) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	if (map_valid_question_mark(&cub->map) == EXIT_FAILURE)
	{
		printf("Validation didnt succed\n");
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
