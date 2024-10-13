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

	intersection.hit = 0;
	oc = vec_sub(sphere->pos, ray.origin);
	a = vec_dot(ray.dest, ray.dest);
	b = -2.0 * vec_dot(oc, ray.dest);
	c = vec_dot(oc, oc) - (sphere->diameter / 2) * (sphere->diameter / 2);
	disc = b * b - 4 * a * c;

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
		}
	}

	if (intersection.hit == 1)
		printf("SPHERE!\n");
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
		intersection.norm = plane->norm; // Normal is constant
	}

	if (intersection.hit == 1)
		printf("PLANE!\n");
	return intersection;
}

t_intersection	intersect_cylinder(t_ray ray, t_cyl *cyl, t_intersection intersection)
{
	// Define necessary vectors
	t_vec oc = vec_sub(ray.origin, cyl->pos); // O - P (P is the base position of the obj)
	t_vec axis = vec_normalize(cyl->norm); // Normalize the obj axis
	double radius_squared = (cyl->diameter / 2) * (cyl->diameter / 2);
		
	// Compute coefficients for the quadratic equation
	double a = vec_dot(ray.dest, ray.dest) - vec_dot(ray.dest, axis) * vec_dot(ray.dest, axis);
	double b = 2.0 * (vec_dot(oc, ray.dest) - vec_dot(ray.dest, axis) * vec_dot(oc, axis));
	double c = vec_dot(oc, oc) - vec_dot(oc, axis) * vec_dot(oc, axis) - radius_squared;

	double discriminant = b * b - 4 * a * c;

	if (discriminant < 0) {
		return intersection; // No intersection
	}

	// Calculate the two potential intersection distances
	double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	double t2 = (-b + sqrt(discriminant)) / (2.0 * a);
		
	double t;
	if (t1 < t2 && t1 > 0) {
		t = t1;
	} else if (t2 > 0) {
		t = t2;
	} else {
		t = INFINITY; // No valid intersection
	}

	if (t < INFINITY) {
		intersection.hit = 1;
		intersection.distance = t;
		intersection.point = vec_add(ray.origin, vec_scalar(ray.dest, t)); // Intersection point
		
		// Check if the intersection point is within the height of the obj
		t_vec point_on_axis = vec_add(cyl->pos, vec_scalar(axis, vec_dot(vec_sub(intersection.point, cyl->pos), axis)));
		double height_check = vec_dot(vec_sub(intersection.point, point_on_axis), axis);

		if (height_check < 0 || height_check > cyl->height) {
			intersection.hit = 0; // Outside the obj's caps
			return intersection;
		}

		intersection.norm = vec_normalize(vec_sub(intersection.point, point_on_axis)); // Normal vector
	}

	if (intersection.hit == 1)
		printf("CYLINDER!\n");
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
	intersection.point = vec(0, 0, 0);
	intersection.norm = vec(0, 0, 0);
	intersection.emittance = ret_color(0, 0, 0);
	// Call the specific intersection test based on the object type
	if (obj->type == SPHERE)
		return (intersect_sphere(ray, (t_sphere *)obj->data, intersection));
	else if (obj->type == CYLINDER)
		return (intersect_cylinder(ray, (t_cyl *)obj->data, intersection));
	else if (obj->type == PLANE)
		return (intersect_plane(ray, (t_plane *)obj->data, intersection));
	/* else if (obj->type == LIGHT)
		return (intersect_light(ray, obj, intersection)); */
	else
		printf("Error\nNo object type for intersection\n");
	return (intersection);
}

t_intersection	find_path(t_ray ray, t_world *world)
{
	t_intersection	closest_intersection;
	t_intersection	intersection;
	t_obj			*object;
	double			closest_distance = INFINITY;

	closest_intersection.hit = 0;
	object = world->obj;
	while (object)
	{
		intersection = intersect(ray, object);
		if (intersection.hit)
		{
			if (intersection.distance < closest_distance)
			{
				closest_distance = intersection.distance;
				closest_intersection = intersection;
			}
		}
		object = object->next;
	}

	return (closest_intersection);
}