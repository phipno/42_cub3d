/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:13:20 by pnolte            #+#    #+#             */
/*   Updated: 2022/04/13 11:34:42 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*cpy;

	while (*lst != NULL)
	{
		cpy = (*lst)->next;
		(*del)((*lst)->content);
		free(*lst);
		*lst = cpy;
	}
	*lst = NULL;
}
