/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:56:58 by pnolte            #+#    #+#             */
/*   Updated: 2022/06/01 10:53:55 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read(char *remember, int fd)
{
	char	*buffer;
	int		byte_read;

	buffer = malloc(sizeof(char) * BUFFER_SIZE);
	if (buffer == NULL)
		return (NULL);
	byte_read = 1;
	while (byte_read != 0 && (!ft_strchr(remember, '\n')))
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		remember = ft_strjoin(remember, buffer, byte_read);
	}
	free(buffer);
	return (remember);
}

char	*ft_cut(char *remember)
{
	char	*new_line;
	int		i;

	i = 0;
	if (remember == NULL || remember[0] == '\0')
		return (NULL);
	while (remember[i] != '\0' && remember[i] != '\n')
		i++;
	if (ft_strchr(remember, '\n'))
		new_line = malloc(sizeof(char) * (i + 2));
	else
		new_line = malloc(sizeof(char) * (i + 1));
	if (new_line == NULL)
		return (NULL);
	i = 0;
	while (remember[i] != '\n' && remember[i] != '\0')
	{
		new_line[i] = remember[i];
		i++;
	}
	if (remember[i] == '\n')
		new_line[i++] = '\n';
	new_line[i] = '\0';
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	*remember[OPEN_MAX];
	char		*line;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remember[fd] = ft_read(remember[fd], fd);
	if (remember[fd] == NULL)
		return (NULL);
	line = ft_cut(remember[fd]);
	i = 0;
	while (remember[fd][i] != '\n' && remember[fd][i] != '\0')
		i++;
	remember[fd] = ft_substr(remember[fd], i + 1, ft_strlen(remember[fd]));
	return (line);
}

// int main(void)
// {
// 	int i;
//     int j;
// 	char *p;

// 	p = NULL;
//     j = open("test1.txt", O_RDONLY);
// 	i = open("multiple_line_no_nl", O_RDONLY);
// 	p = get_next_line(i);
// 	printf("Result:%s\n", p);
// 	free(p);
//     p = get_next_line(j);
// 	printf("Result:%s\n", p);
// 	free(p);
// 	p = get_next_line(i);
// 	printf("Result:%s\n", p);
// 	free(p);
//     p = get_next_line(j);
// 	printf("Result:%s\n", p);
// 	free(p);
// 	p = get_next_line(i);
// 	printf("Result:%s\n", p);
// 	free(p);
//     p = get_next_line(j);
// 	printf("Result:%s\n", p);
// 	free(p);
// 	p = get_next_line(i);
// 	printf("Result:%s\n", p);
// 	free(p);
// 	p = get_next_line(i);
// 	printf("Result:%s\n", p);
// 	free(p);
// 	p = get_next_line(i);
// 	printf("Result:%s\n", p);
// 	free(p);
// 	return (0);
// }
