#include "minirt.h"

t_intersection	intersect_sphere(t_ray ray, t_sphere *sphere, t_intersection intersection)
{
	double	a;
	double	b;
	double	c;
	double	disc;
	double	t1;
	double	t2;
	double	t;
	t_vec	oc;

		// Compute coefficients for the quadratic equation
	oc = vec_sub(sphere->pos, ray.origin);
	a = vec_dot(ray.dest, ray.dest);
	b = -2.0 * vec_dot(oc, ray.dest);
	c = vec_dot(oc, oc) - (sphere->diameter / 2) * (sphere->diameter / 2);
	disc = b * b - 4 * a * c;

		// Check if 2 points of intersection are correct
	if (disc < 0)
		return (intersection);
	else
	{
		t1 = (-b - sqrt(disc)) / (2.0 * a);
		t2 = (-b + sqrt(disc)) / (2.0 * a);
		if (t1 < t2 && t1 > 0)
			t = t1;
		else if (t2 > 0)
			t = t2;
		else
			t = INFINITY;
		if (t < INFINITY)
		{
			intersection.hit = 1;
			intersection.distance = t;
			intersection.point = vec_add(ray.origin, vec_scalar(ray.dest, t));
			intersection.norm = vec_normalize(vec_sub(intersection.point, sphere->pos));
			intersection.color = sphere->color;
		}
	}

	return (intersection);
}

t_intersection	intersect_plane(t_ray ray, t_plane *plane, t_intersection intersection)
{
	double denominator = vec_dot(ray.dest, plane->norm);
	if (fabs(denominator) < 1e-6)
		return intersection; // Ray is parallel to the plane

	double t = vec_dot(vec_sub(plane->pos, ray.origin), plane->norm) / denominator;
	if (t >= 0)
	{
		intersection.hit = 1;
		intersection.distance = t;
		intersection.point = vec_add(ray.origin, vec_scalar(ray.dest, t)); // O + tD
		intersection.norm = vec_normalize(plane->norm);
		if (vec_dot(ray.dest, intersection.norm) > 0)
			intersection.norm = vec_scalar(intersection.norm, -1); // Flip normal
		intersection.color = plane->color;
	}

	return intersection;
}

t_intersection	intersect_cylinder(t_ray ray, t_cyl *cyl, t_intersection intersection)
{
	ray.dest = vec_normalize(ray.dest);
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
		return (intersection);
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
		}
	}
	return (intersection);
}

/* t_intersection	intersect_light(t_ray ray, t_obj *obj, t_intersection intersection)
{
	return (intersection);
} */

t_intersection	intersect(t_ray ray, t_obj *obj)
{
	t_intersection intersection;

	intersection.hit = 0;
	intersection.distance = INFINITY;
	intersection.point = vec(0, 0, 0, 0);
	intersection.norm = vec(0, 0, 0, 0);

	intersection.reflectance = 1;
	intersection.diffuse = 0.5;
	intersection.specular = 0.94;

	if (obj->type == SPHERE)
		return (intersect_sphere(ray, (t_sphere *)obj->data, intersection));
	else if (obj->type == CYLINDER)
		return (intersect_cylinder(ray, (t_cyl *)obj->data, intersection));
	else if (obj->type == PLANE)
		return (intersect_plane(ray, (t_plane *)obj->data, intersection));
	/* else
		printf("Error\nNo object type for intersection\n"); */
	return (intersection);
}

int	is_occluded(t_ray shadow_ray, t_world *world, double light_distance)
{
	t_obj *object = world->objlist;
	t_intersection intersection;

	while (object) {
		intersection = intersect(shadow_ray, object);
		if (intersection.hit && intersection.distance < light_distance) {
			return (1); // Occlusion detected
		}
		object = object->next;
	}
	return (0); // No occlusion
}

t_intersection	find_path(t_ray ray, t_world *world)
{
	double			closest_distance;
	t_intersection	closest_intersection;
	t_intersection	intersection;
	t_obj			*object;

	closest_distance = INFINITY;
	closest_intersection.hit = 0;
	object = world->objlist;
		// iterate over all objects and get the closest one
	while (object)
	{
		if (object->type > 3)
		{
			intersection = intersect(ray, object);
			if (intersection.hit && intersection.distance < closest_distance)
			{
				closest_distance = intersection.distance;
				closest_intersection = intersection;
			}
		}
		object = object->next;
	}
	return (closest_intersection);
}