/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:40:56 by fjoestin          #+#    #+#             */
/*   Updated: 2024/11/20 12:39:47 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	*add_sobj(int type, void *list)
{
	t_obj	*new;
	new = malloc(sizeof(t_obj));
	new->type = type;
	new->data = list;
	new->next = NULL;
	return (new);
}

// t_obj	*add_light(t_light *lightlist) // del
// {
// 	t_light	*temp;
// 	t_obj	*new;

// 	temp = lightlist;
// 	while (temp->next)
// 		temp = temp->next;
// 	new = malloc(sizeof(t_obj));
// 	new->type = LIGHT;
// 	new->data = temp;
// 	new->next = NULL;
// 	return (new);
// }

t_obj	*ft_add_obj_lst(int type, t_world *world, t_obj **objlist)
{
	if(type < 1)
		return(NULL);
	t_obj	*new;
	void	*last;

	new = NULL;
	if (type == AMBIENCE)
		new = add_sobj(type, world->amb);
	else if (type == CAMERA)
		new = add_sobj(type, world->cam);
	else if (type == LIGHT){
		last = ft_lstlast_lig_mrt(world->light);
		new = add_sobj(type, last);
	}
	else if (type == SPHERE)
	{
		last = (void *)ft_lstlast_sphere_mrt(world->sphere);
		new = add_sobj(type, last);
	}
	else if (type == PLANE)
	{
		last = (void *)ft_lstlast_plane_mrt(world->plane);
		new = add_sobj(type, last);
	}
	else if (type == CYLINDER)
	{
		last = (void *)ft_lstlast_cyl_mrt(world->cyl);
		new = add_sobj(type, last);
	}
	ft_lstadd_back_mrt(objlist, new);
	return (*objlist);
}

void	ft_lstadd_back_mrt(t_obj **lst, t_obj *new)
{
	t_obj	*last;

	last = ft_lstlast_mrt(*lst);
	if (!last)
		*lst = new;
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