/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:39:58 by fjoestin          #+#    #+#             */
/*   Updated: 2024/12/19 17:38:36 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Removed free(obj->data)??? check if this causes issues
static void	free_obj(t_obj *obj)
{
	t_obj	*next;

	if (!obj)
		return ;
	while (obj)
	{
		next = obj->next;
		free(obj->data);
		free(obj);
		obj = next;
	}
}

/* static void	free_sphere(t_sphere *sphere)
{
	t_sphere	*next;

	if (!sphere)
		return ;
	while (sphere)
	{
		next = sphere->next;
		free(sphere);
		sphere = next;
	}
} */

void	free_world(t_world *world)
{
	if (!world)
		return ;
	if (world->amb)
		free(world->amb);
	if (world->objlist)
		free_obj(world->objlist);
	free(world);
}
