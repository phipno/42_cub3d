/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:00:59 by pnolte            #+#    #+#             */
/*   Updated: 2022/04/19 15:46:45 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**word_count_p(char const *s, char c, char **p, int *count_p)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			(*count_p)++;
		i++;
	}
	p = malloc((*count_p + 1) * sizeof(char *));
	if (p == NULL)
		return (NULL);
	p[*count_p] = NULL;
	return (p);
}

static int	where(char const *s, char c, int begin)
{
	int	end;

	end = begin;
	while (s[end] != '\0')
	{
		if (s[end] != c && (s[end + 1] == c || s[end + 1] == '\0'))
			break ;
		end++;
	}
	return (end);
}

static char	**freeee(char **p, int h)
{
	int	i;

	i = 0;
	if (p[h] == NULL)
	{
		while (p[i])
		{
			free(p[i]);
			i++;
		}
		free(p);
		return (NULL);
	}
	return (p);
}

static void	check(int *h, int *begin, int end)
{
	*begin = end + 1;
	(*h)++;
}

char	**ft_split(char const *s, char c)
{
	int		end;
	int		begin;
	int		count_p;
	int		h;
	char	**p;

	p = NULL;
	if (s == NULL)
		return (NULL);
	count_p = 0;
	p = word_count_p(s, c, p, &count_p);
	begin = 0;
	h = 0;
	while (s[begin] != '\0' && count_p != 0 && p != NULL)
	{
		while (s[begin] == c)
			begin++;
		if (s[begin] == '\0')
			break ;
		end = where(s, c, begin);
		p[h] = ft_substr(s, begin, (end - begin + 1));
		p = freeee(p, h);
		check(&h, &begin, end);
	}
	return (p);
}

// int main(void)
// {
// 	char	s[] = "         split       this for   me  !        ";
// 	char	c = ' ';
// 	char	**p;
// 	int		i;

// 	i = 0;
// 	p = ft_split(s, c);
// 	while (p[i] != NULL)
// 	{
// 		printf("%s\n", p[i]);
// 		i++;
// 	}
// }
