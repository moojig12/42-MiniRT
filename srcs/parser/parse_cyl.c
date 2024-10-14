/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cyl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:08:01 by fjoestin          #+#    #+#             */
/*   Updated: 2024/10/14 21:49:42 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_lstadd_back_cyl_mrt(t_cyl **lst, t_cyl *new)
{
	t_cyl	*last;

	last = ft_lstlast_cyl_mrt(*lst);
	if (!last)
		*lst = new;
	else
	{
		last->next = new;
		new->next = NULL;
	}
}

t_cyl	*ft_lstlast_cyl_mrt(t_cyl *lst)
{
	t_cyl	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
	{
		temp = temp->next;
	}
	return (temp);
}

t_cyl	*parse_cyl(t_world *world, char **input)
{
	t_cyl *new;
	new = malloc(sizeof(t_cyl)); 
	// if (index > 5 || index < 1)
		// printf("Error\nInvalid input for cylinder\n");
	if (input[1])
		pop_vec(&obj->pos, ft_split(input, ','), NULL);
	if (input[2])
		pop_vec(&obj->norm, ft_split(input, ','), alloc_float(-1.0, 1.0));
	if (input[3])
		obj->diameter = ft_atof(input);
	if (input[4])
		obj->height = ft_atof(input);
	if (input[5])
		pop_color(&obj->color, ft_split(input, ','));
	ft_lstadd_back_cyl_mrt(&world->cyl, new);
	return (world->cyl);
}