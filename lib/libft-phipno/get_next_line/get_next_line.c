/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:00:22 by pnolte            #+#    #+#             */
/*   Updated: 2022/07/06 11:28:08 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_read(char *remember, int fd)
{
	char	*buffer;
	int		byte_read;

	buffer = malloc(sizeof(char) * BUFFER_SIZE);
	if (buffer == NULL)
		return (NULL);
	byte_read = 1;
	while (byte_read != 0 && (!gnl_strchr(remember, '\n')))
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		remember = gnl_strjoin(remember, buffer, byte_read);
	}
	free(buffer);
	return (remember);
}

char	*gnl_cut(char *remember)
{
	char	*new_line;
	int		i;

	i = 0;
	if (remember == NULL || remember[0] == '\0')
		return (NULL);
	while (remember[i] != '\0' && remember[i] != '\n')
		i++;
	if (gnl_strchr(remember, '\n'))
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
	static char	*remember;
	char		*line;
	int			i;

	if (read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remember = gnl_read(remember, fd);
	if (remember == NULL)
		return (NULL);
	line = gnl_cut(remember);
	i = 0;
	while (remember[i] != '\n' && remember[i] != '\0')
		i++;
	remember = gnl_substr(remember, i + 1, gnl_strlen(remember));
	return (line);
}

// int main(void)
// {
// 	int i;
// 	char *p;

// 	p = NULL;
// 	i = open("alternate_line_nl_no_nl", O_RDONLY);
// 	p = get_next_line(i);
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
// 	p = get_next_line(i);
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
// 	// check_leaks();
// 	return (0);
// }
