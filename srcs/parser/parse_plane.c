/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:08:18 by fjoestin          #+#    #+#             */
/*   Updated: 2024/10/14 21:53:08 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_lstadd_back_plane_mrt(t_plane **lst, t_plane *new)
{
	t_plane	*last;

	last = ft_lstlast_plane_mrt(*lst);
	if (!last)
		*lst = new;
	else
	{
		last->next = new;
		new->next = NULL;
	}
}

t_plane	*ft_lstlast_plane_mrt(t_plane *lst)
{
	t_plane	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

int	parse_plane(t_world *world, char **input)
{
	t_plane	*new;
	new = malloc(sizeof(t_plane));
	// if (index > 3 || index < 1)
		// return (0);
	if (input[1])
		pop_vec(&new->pos, ft_split(input, ','), NULL);
	if (input[2])
		pop_vec(&obj->norm, ft_split(input, ','), alloc_float(-1.0, 1.0));
	if (input[3])
		pop_color(&obj->material.color, ft_split(input, ','));
	return (0);
}