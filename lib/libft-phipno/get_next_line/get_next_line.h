/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 12:41:25 by pnolte            #+#    #+#             */
/*   Updated: 2022/07/06 12:04:42 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 10
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

char	*get_next_line(int fd);
char	*gnl_read(char *remember, int fd);
int		gnl_strlen(const char *c);
char	*gnl_strjoin(char *s1, char *s2, int byte_read);
char	*gnl_substr(char *s, int start, int len);
char	*gnl_strchr(const char *str, int c);

#endif
