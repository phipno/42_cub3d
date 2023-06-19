/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wall_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:09:49 by pnolte            #+#    #+#             */
/*   Updated: 2023/06/19 14:44:00 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h> //open
#include <stdio.h> //perror

#include "libft.h"
#include "cub3d.h"
#include "lm_array_str.h"

char	*sub_str_walls(const char *str)
{
	int		i;
	int		fd;
	char	*path_to_wall;

	i = 0;
	//@note this while condition needs more defining
	while (str[i] != '.' && str[i] != '\0')
		i++;
	path_to_wall = ft_substr(str, i, ft_strlen(str));
	fd = open(path_to_wall, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Open \"", 2);
		ft_putstr_fd((char *)str, 2);
		ft_putstr_fd("\" : ", 2);
		perror("");
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "Wall Texutres!");
	}
	close(fd);
	return (path_to_wall);
}

static int	color_integrity(t_rgba *color, const char *str)
{
	int i;

	i = 0;
	while (i < 3)
	{
		if ((color->rgba.b > 255 || color->rgba.b < 0)
			&& (color->rgba.g > 255 || color->rgba.g < 0)
			&& (color->rgba.r > 255 || color->rgba.r < 0))
		{
			ft_putstr_fd("Color: \"", 2);
			ft_putstr_fd((char *)str, 2);
			ft_putstr_fd("\"\n", 2);
			return (false);
		}
		i++;
	}
	return (true);
}

void	split_that_color(t_rgba *color, const char *str)
{
	int		i;
	char	*sub;
	char	**split;

	i = 0;
	while (ft_isdigit(str[i]) == 0 && str[i] != '\0')
		i++;
	sub = ft_substr(str, i, ft_strlen(str));
	split = ft_split(sub, ',');
	printf("Content_Color: %s, R.%s, G.%s, B.%s\n", sub, split[0], split[1], split[2]);
	i = 0;
	while (split[i] != NULL)
		i++;
	if (i < 3)
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "There are not enough colors");
	color->colour = get_rgba(ft_atoi(split[0]), ft_atoi(split[1]), ft_atoi(split[2]), 255);
	lm_array_str_free(split);
	if (color_integrity(color, str) == false)
		cub_exit(EXIT_FAILURE, STDERR_FILENO, "Color should only be in range of 0-255");
}

/* ************************************************************************** */
