/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmandakh <nmandakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:57:44 by fjoestin          #+#    #+#             */
/*   Updated: 2024/12/17 13:01:18 by nmandakh         ###   ########.fr       */
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

void	pop_intersec_sphere(t_intersect *inters, \
double t, t_ray ray, t_sphere *sphere)
{
	inters->hit = 1;
	inters->distance = t;
	inters->point = vec_add(ray.origin, vec_scalar(ray.dest, t));
	inters->norm = vec_normalize(vec_sub(inters->point, sphere->pos));
	inters->point = vec_add(inters->point, vec_scalar(inters->norm, EPSILON));
	inters->color = sphere->color;
	material_init(&inters->material, METAL_ROUGH);
}

t_intersect	find_path(t_ray ray, t_world *world)
{
	double			closest_distance;
	t_intersect		closest_x;
	t_intersect		inter;
	t_obj			*object;

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
				closest_x.emission = (double)object->emissive;
			}
		}
		object = object->next;
	}
	return (closest_x);
}

t_comp	calc_computations(t_ray ray, t_cyl *cyl)
{
	t_vec	oc;
	t_comp	comp;
	double	radius_squared;

	oc = vec_sub(ray.origin, cyl->pos);
	comp.axis = vec_normalize(cyl->norm);
	radius_squared = (cyl->diameter / 2) * (cyl->diameter / 2);
	comp.a = vec_dot(ray.dest, ray.dest) - vec_dot(ray.dest, comp.axis) * \
												vec_dot(ray.dest, comp.axis);
	comp.b = 2.0 * (vec_dot(oc, ray.dest) - vec_dot(ray.dest, comp.axis) \
												* vec_dot(oc, comp.axis));
	comp.c = vec_dot(oc, oc) - vec_dot(oc, comp.axis) \
			* vec_dot(oc, comp.axis) - radius_squared;
	comp.disc = comp.b * comp.b - 4 * comp.a * comp.c;
	return (comp);
}

void	comp_calc_t(t_comp *comp)
{
	comp->t1 = (-comp->b - sqrt(comp->disc)) / (2.0 * comp->a);
	comp->t2 = (-comp->b + sqrt(comp->disc)) / (2.0 * comp->a);
	if (comp->t1 < comp->t2 && comp->t1 > 0)
		comp->t = comp->t1;
	else if (comp->t2 > 0)
		comp->t = comp->t2;
	else
		comp->t = INFINITY;
}
