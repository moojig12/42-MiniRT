/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmandakh <nmandakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:19:47 by nmandakh          #+#    #+#             */
/*   Updated: 2023/11/22 12:33:05 by nmandakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*el;
	t_list	*elem;

	if (lst != 0 && lst[0] != 0)
	{
		el = lst[0];
		while (el->next != NULL)
		{
			del(el->content);
			elem = el;
			el = el->next;
			free(elem);
		}
		del(el->content);
		free(el);
		lst[0] = NULL;
	}
}
