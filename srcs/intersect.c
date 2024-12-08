/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:29:59 by fjoestin          #+#    #+#             */
/*   Updated: 2024/12/08 16:22:43 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_x	intersect_sphere(t_ray ray, t_sphere *sphere, t_x inters)
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
			pop_intersec(&inters, c, ray, sphere);
	}
	return (inters);
}

t_x	intersect_plane(t_ray ray, t_plane *plane, t_x *intersc)
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

t_x	intersect_cylinder(t_ray ray, t_cyl *cyl, t_x inter)
{
	// ray.dest = vec_normalize(ray.dest);
	t_vec oc = vec_sub(ray.origin, cyl->pos);
	t_vec axis = vec_normalize(cyl->norm);
	double radius_squared = (cyl->diameter / 2) * (cyl->diameter / 2);

		// Compute coefficients for the quadratic equation
	double a = vec_dot(ray.dest, ray.dest) - vec_dot(ray.dest, axis) * vec_dot(ray.dest, axis);
	double b = 2.0 * (vec_dot(oc, ray.dest) - vec_dot(ray.dest, axis) * vec_dot(oc, axis));
	double c = vec_dot(oc, oc) - vec_dot(oc, axis) * vec_dot(oc, axis) - radius_squared;

	double discriminant = b * b - 4 * a * c;

		// Check if 2 points of intersection are correct
	if (discriminant < 0)
		return (inter);
	else
	{
		double t;
		double	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
		double	t2 = (-b + sqrt(discriminant)) / (2.0 * a);

		if (t1 < t2 && t1 > 0)
			t = t1;
		else if (t2 > 0)
			t = t2;
		else
			t = INFINITY;

		if (t < INFINITY)
		{
			intersection.distance = t;
			intersection.point = vec_add(ray.origin, vec_scalar(ray.dest, t));

			// Check t1 against height projection
			double projection1 = vec_dot(vec_sub(vec_add(ray.origin, vec_scalar(ray.dest, t1)), cyl->pos), axis);
			if (t1 > 0 && projection1 >= 0.0001 && projection1 <= cyl->height)
			{
				t = t1;
				intersection.hit = 1;
			}

			// Check t2 only if t1 is invalid or farther
			double projection2 = vec_dot(vec_sub(vec_add(ray.origin, vec_scalar(ray.dest, t2)), cyl->pos), axis);
			if ((!intersection.hit || t2 < t) && t2 > 0 && projection2 >= 0.0001 && projection2 <= cyl->height)
			{
				t = t2;
				intersection.hit = 1;
			}
			// If no valid intersection was found, return no-hit intersection
			if (!intersection.hit)
				return intersection;
			// Calculate intersection details
			intersection.distance = t;
			intersection.point = vec_add(ray.origin, vec_scalar(ray.dest, t));
			// Calculate point on cylinder axis
			double projection = vec_dot(vec_sub(intersection.point, cyl->pos), axis);
			t_vec point_on_axis = vec_add(cyl->pos, vec_scalar(axis, projection));

			intersection.norm = vec_normalize(vec_sub(intersection.point, point_on_axis));
			intersection.color = cyl->color;

			// If point of impact is inside cylinder invert the normal
			if (vec_dot(ray.dest, intersection.norm) > 0)
				intersection.norm = vec_scalar(intersection.norm, -1);
			intersection.point = vec_add(intersection.point, vec_scalar(intersection.norm, EPSILON));
		}
	}
	return (intersection);
}

t_x	intersect(t_ray ray, t_obj *obj)
{
	t_x	inter;

	inter.hit = 0;
	inter.distance = INFINITY;
	inter.point = vec(0, 0, 0, 0);
	inter.norm = vec(0, 0, 0, 0);
	inter.reflectance = 0.5;
	inter.diffuse = 0.5;
	inter.specular = 0.0;
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
	t_x		inter;

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
