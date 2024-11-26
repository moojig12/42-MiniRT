/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:39:58 by fjoestin          #+#    #+#             */
/*   Updated: 2024/11/26 17:58:51 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static void	free_obj(t_obj *obj);
static void	free_light(t_light *light);
static void	free_sphere(t_sphere *sphere);
static void	free_plane(t_plane *plane);
static void	free_cyl(t_cyl *cyl);

void	free_world(t_world *world)
{
	if (!world)
		return ;
	if (world->amb)
		free(world->amb);
	if (world->cam)
		free(world->cam);
	if (world->light)
		free_light(world->light);
	if (world->sphere)
		free_sphere(world->sphere);
	if (world->plane)
		free_plane(world->plane);
	if (world->cyl)
		free_cyl(world->cyl);
	if (world->objlist)
		free_obj(world->objlist); // see if I'm not freeing *data too times
	free(world);
}
static void	free_obj(t_obj *obj)
{
	t_obj	*next;
	
	if (!obj)
		return;
	while (obj)
	{
		next = obj->next;
		//free(obj->data);
		free(obj);
		obj = next;
	}
}
static void	free_light(t_light *light)
{
	t_light	*next;
	
	if (!light)
		return;
	while (light)
	{
		next = light->next;
		free(light);
		light = next;
	}
}
static void	free_sphere(t_sphere *sphere)
{
	t_sphere	*next;
	
	if (!sphere)
		return;
	while (sphere)
	{
		next = sphere->next;
		free(sphere);
		sphere = next;
	}
}
static void	free_plane(t_plane *plane)
{
	t_plane	*next;
	
	if (!plane)
		return;
	while (plane)
	{
		next = plane->next;
		free(plane);
		plane = next;
	}
}
static void	free_cyl(t_cyl *cyl)
{
	t_cyl	*next;
	
	if (!cyl)
		return;
	while (cyl)
	{
		next = cyl->next;
		free(cyl);
		cyl = next;
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}