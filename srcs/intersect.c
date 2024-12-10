/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:29:59 by fjoestin          #+#    #+#             */
/*   Updated: 2024/12/09 14:54:50 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersect	intersect_sphere(t_ray ray, t_sphere *sphere, t_intersect inters)
{
	double	a;
	double	b;
	double	c;
	double	disc;
	t_vec	oc;

	oc = vec_sub(sphere->pos, ray.origin);
	a = vec_dot(ray.dest, ray.dest);
	b = -2.0 * vec_dot(oc, ray.dest);
	c = vec_dot(oc, oc) - (sphere->diameter / 2) * (sphere->diameter / 2);
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return (inters);
	else
	{
		c = calc_t(a, b, disc);
		if (c < INFINITY)
			pop_intersec_sphere(&inters, c, ray, sphere);
		material_init(&inters.material, MIRROR);
	}
	return (inters);
}

t_intersect	intersect_plane(t_ray ray, t_plane *plane, t_intersect *intersc)
{
	double	denom;
	double	t;

	denom = vec_dot(ray.dest, plane->norm);
	if (fabs(denom) < 1e-6)
		return (*intersc);
	t = vec_dot(vec_sub(plane->pos, ray.origin), plane->norm) / denom;
	if (t >= 0)
	{
		intersc->hit = 1;
		intersc->distance = t;
		intersc->point = vec_add(ray.origin, vec_scalar(ray.dest, t));
		intersc->norm = plane->norm;
		if (denom > 0)
			intersc->norm = vec_scalar(intersc->norm, -1);
		intersc->point = vec_add(intersc->point, 
				vec_scalar(intersc->norm, EPSILON));
		intersc->color = plane->color;
	}
	return (*intersc);
}

t_intersect	intersect_cylinder(t_ray ray, t_cyl *cyl, t_intersect inter)
{
	t_comp	comp;

	comp = calc_computations(ray, cyl);
	if (comp.disc < 0)
		return (inter);
	else
	{
		comp_calc_t(&comp);
		if (comp.t < INFINITY)
		{
			calc_projection(ray, &comp, cyl, &inter);
			if (!inter.hit)
				return (inter);
			pop_intersec_cyl(ray, &inter, comp, cyl);
			if (vec_dot(ray.dest, inter.norm) > 0)
				inter.norm = vec_scalar(inter.norm, -1);
			inter.point = vec_add(inter.point, vec_scalar(inter.norm, EPSILON));
			material_init(&inter.material, ROCK);
		}
	}
	return (inter);
}

t_intersect	intersect(t_ray ray, t_obj *obj)
{
	t_intersect	inter;

	inter.hit = 0;
	inter.distance = INFINITY;
	inter.point = vec(0, 0, 0, 0);
	inter.norm = vec(0, 0, 0, 0);
	material_init(&inter.material, 0);
	ray.dest = vec_normalize(ray.dest);
	if (obj->type == SPHERE)
		return (intersect_sphere(ray, (t_sphere *)obj->data, inter));
	else if (obj->type == CYLINDER)
		return (intersect_cylinder(ray, (t_cyl *)obj->data, inter));
	else if (obj->type == PLANE)
		return (intersect_plane(ray, (t_plane *)obj->data, &inter));
	return (inter);
}

int	is_occluded(t_ray shadow_ray, t_world *world, double light_distance)
{
	t_obj	*object;
	t_intersect		inter;

	object = world->objlist;
	while (object)
	{
		inter = intersect(shadow_ray, object);
		if (inter.hit && inter.distance < light_distance)
			return (1);
		object = object->next;
	}
	return (0);
}
