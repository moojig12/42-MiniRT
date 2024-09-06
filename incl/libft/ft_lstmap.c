/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmandakh <nmandakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:42:51 by nmandakh          #+#    #+#             */
/*   Updated: 2023/11/22 13:30:05 by nmandakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*temp;
	void	*p1;

	if (!lst || !f)
		return (NULL);
	new = NULL;
	temp = NULL;
	while (lst)
	{
		p1 = f(lst->content);
		temp = ft_lstnew(p1);
		if (temp == NULL)
		{
			ft_lstclear(&new, del);
			free(p1);
			return (NULL);
		}
		ft_lstadd_back(&new, temp);
		lst = lst->next;
	}
	return (new);
}
