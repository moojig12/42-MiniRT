/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:39:58 by fjoestin          #+#    #+#             */
/*   Updated: 2024/12/17 14:08:47 by fjoestin         ###   ########.fr       */
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
		free(obj);
		obj = next;
	}
}

static void	free_sphere(t_sphere *sphere)
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
}

void	free_world(t_world *world)
{
	if (!world)
		return ;
	if (world->amb)
		free(world->amb);
	if (world->cam)
		free(world->cam);
	if (world->light)
		free(world->light);
	if (world->sphere)
		free_sphere(world->sphere);
	if (world->plane)
		free_plane(world->plane);
	if (world->cyl)
		free_cyl(world->cyl);
	if (world->objlist)
		free_obj(world->objlist);
	if (world->selected)
		free(world->selected);
	free(world);
}
