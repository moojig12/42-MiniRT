/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:40:56 by fjoestin          #+#    #+#             */
/*   Updated: 2024/10/14 21:51:44 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	*add_sobj(int type, void *list) // del
{
	t_obj	*new;
	new = malloc(sizeof(t_obj));
	new->type = type;
	new->data = list;
	new->next = NULL;
	return (new);
}

t_obj	*add_light(t_light *lightlist) // del
{
	t_light	*temp;
	t_obj	*new;

	temp = lightlist;
	while (temp->next)
		temp = temp->next;
	new = malloc(sizeof(t_obj));
	new->type = LIGHT;
	new->data = temp;
	new->next = NULL;
	return (new);
}
t_obj	*add_obj(int type, void *list)
{
	t_obj	*new;
	new = malloc(sizeof(t_obj));
	while(list->next)
		list = list->next;
	new->type = type;
	new->data = list;
	new->next = NULL;
	return (new);
}

t_obj	*ft_add_obj_lst(int type, t_world *world, t_obj **objlist)
{
	if(type < 1)
		return(NULL);
	t_obj	*new;
	void	*last;
	if (type == AMBIENCE)
		new = add_sobj(type, world->amb);
	else if (type == CAMERA)
		new = add_sobj(type, world->cam);
	else if (type == LIGHT)
		new = add_light(world->light);
	else if (type == SPHERE)
	{
		last = ft_lstl
		new = add_obj(type, world->sphere);
	}
	else if (type == PLANE)
	{
		last
		new = add_obj(type, last);
	}
	else if (type == CYLINDER)
	{
		last = ft_lstlast_cyl_mrt(world->cyl);
		new = add_obj(type, last);
	}
	ft_lstadd_back_mrt(&objlist, new);
}

void	ft_lstadd_back_mrt(t_obj **lst, t_obj *new)
{
	t_obj	*last;

	last = ft_lstlast_mrt(*lst);
	if (!last)
		*lst = new
	else
		last->next = new;
}
t_obj	*ft_lstlast_mrt(t_obj *lst)
{
	t_obj	*temp;

	if(!lst)
	return (NULL);
	temp = lst;
	while (temp->next)
	{
		temp = temp->next;
	}
	return (temp);
}