/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:56:52 by pnolte            #+#    #+#             */
/*   Updated: 2022/06/01 10:51:54 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef  BUFFER_SIZE
#  define BUFFER_SIZE = 100
# endif
# include <limits.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

char	*get_next_line(int fd);
char	*ft_read(char *remember, int fd);
int		ft_strlen(const char *c);
char	*ft_strjoin(char *s1, char *s2, int byte_read);
char	*ft_substr(char *s, int start, int len);
char	*ft_strchr(const char *str, int c);

#endif
