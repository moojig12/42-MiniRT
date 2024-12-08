/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:57:44 by fjoestin          #+#    #+#             */
/*   Updated: 2024/12/08 16:24:15 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	calc_t(double a, double b, double disc)
{
	double	t1;
	double	t2;
	double	t;

	t1 = (-b - sqrt(disc)) / (2.0 * a);
	t2 = (-b + sqrt(disc)) / (2.0 * a);
	if (t1 < t2 && t1 > 0)
		t = t1;
	else if (t2 > 0)
		t = t2;
	else
		t = INFINITY;
	return (t);
}

void	pop_intersec(t_x *inters, double t, t_ray ray, t_sphere *sphere)
{
	inters->hit = 1;
	inters->distance = t;
	inters->point = vec_add(ray.origin, vec_scalar(ray.dest, t));
	inters->norm = vec_normalize(vec_sub(inters->point, sphere->pos));
	inters->point = vec_add(inters->point, vec_scalar(inters->norm, EPSILON));
	inters->color = sphere->color;
	inters->diffuse = sphere->material.diffuse;
	inters->reflectance = sphere->material.reflect;
}

t_x	find_path(t_ray ray, t_world *world)
{
	double	closest_distance;
	t_x		closest_x;
	t_x		inter;
	t_obj	*object;

	closest_distance = INFINITY;
	closest_x.hit = 0;
	object = world->objlist;
	while (object)
	{
		if (object->type > 3)
		{
			inter = intersect(ray, object);
			if (inter.hit && inter.distance < closest_distance)
			{
				closest_distance = inter.distance;
				closest_x = inter;
			}
		}
		object = object->next;
	}
	return (closest_x);
}

