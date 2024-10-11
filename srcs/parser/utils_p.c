/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:47:03 by fjoestin          #+#    #+#             */
/*   Updated: 2024/10/07 16:47:35 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
t_obj	*add_sobj(int type, void *list)
{
	t_obj	*new;
	new = malloc(sizeof(t_obj));
	new->type = type;
	new->data = list;
	new->next = NULL;
	return (new);
}

t_obj	*add_light(t_light *lightlist)
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
	if (type == AMBIENCE)
		new = add_sobj(type, world->amb);
	else if (type == CAMERA)
		new = add_sobj(type, world->cam);
	else if (type == LIGHT)
		new = add_light(world->light);
	else if (type == SPHERE)
		new = add_obj(type, world->sphere);
	else if (type == PLANE)
		new = add_obj(type, world->plane);
	else if (type == CYLINDER)
		new = add_obj(type, world->cyl);
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

void	ft_lstadd_back_lig_mrt(t_light **lst, t_light *new)
{
	t_light	*last;

	last = ft_lstlast_lig_mrt(*lst);
	if (!last)
		*lst = new;
	else
	{
		last->next = new;
		new->next = NULL;
	}
}

t_light	*ft_lstlast_lig_mrt(t_light *lst)
{
	t_light	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
	{
		temp = temp->next;
	}
	return (temp);
}