/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wall_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:09:49 by pnolte            #+#    #+#             */
/*   Updated: 2023/05/24 15:22:51 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h> //open
#include <stdio.h> //perror

#include "libft.h"
#include "cub3d.h"

int	sub_str_walls(char **write_to, const char *str)
{
	int		i;
	int		fd;

	i = 0;
	//@note this while condition needs more defining
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

static int	color_integrity(int write_to[3], const char *str)
{
	int i;

	i = 0;
	while (i < 3)
	{
		if (write_to[i] > 255 || write_to[i] < 0)
		{
			ft_putstr_fd("Color Error: \"", 2);
			ft_putstr_fd((char *)str, 2);
			ft_putstr_fd("\"\n", 2);
			return (false);
		}
		i++;
	}
	return (true);
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
	if (color_integrity(write_to, str) == false)
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
