#include "minirt.h"

t_intersection	intersect_sphere(t_ray ray, t_obj *obj)
{
	t_intersection	intersection;
	double	a;
	double	b;
	double	c;
	double	disc;
	double	t1;
	double	t2;
	double	t;
	t_vec	oc;

	intersection.hit = 0;
	oc = subtract(ray.origin, obj->pos);
	a = dot(ray.dest, ray.dest);
	b = 2.0 * dot(oc, ray.dest);
	c = dot(oc, oc) - (obj->diameter / 2) * (obj->diameter / 2);
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
			intersection.point = add(ray.origin, vec_scalar(ray.dest, t));
			intersection.norm = normalize(subtract(intersection.point, obj->pos));
		}
	}
	return (intersection);
}

t_intersection	intersect_plane(t_ray ray, t_obj *obj)
{
	t_intersection intersection;
	intersection.hit = 0;

	double denominator = dot(ray.dest, obj->norm);
	if (fabs(denominator) < 1e-6)
		return intersection; // Ray is parallel to the plane

	double t = dot(subtract(obj->pos, ray.origin), obj->norm) / denominator;
	if (t >= 0)
	{
		intersection.hit = 1;
		intersection.distance = t;
		intersection.point = add(ray.origin, vec_scalar(ray.dest, t)); // O + tD
		intersection.norm = obj->norm; // Normal is constant
	}

	return intersection;
}

t_intersection	intersect_cylinder(t_ray ray, t_obj *obj)
{
	t_intersection intersection;
	intersection.hit = 0;

	// Define necessary vectors
	t_vec oc = subtract(ray.origin, obj->pos); // O - P (P is the base position of the obj)
	t_vec axis = normalize(obj->norm); // Normalize the obj axis
	double radius_squared = (obj->diameter / 2) * (obj->diameter / 2);
		
	// Compute coefficients for the quadratic equation
	double a = dot(ray.dest, ray.dest) - dot(ray.dest, axis) * dot(ray.dest, axis);
	double b = 2.0 * (dot(oc, ray.dest) - dot(ray.dest, axis) * dot(oc, axis));
	double c = dot(oc, oc) - dot(oc, axis) * dot(oc, axis) - radius_squared;

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
		intersection.point = add(ray.origin, vec_scalar(ray.dest, t)); // Intersection point
		
		// Check if the intersection point is within the height of the obj
		t_vec point_on_axis = add(obj->pos, vec_scalar(axis, dot(subtract(intersection.point, obj->pos), axis)));
		double height_check = dot(subtract(intersection.point, point_on_axis), axis);

		if (height_check < 0 || height_check > obj->height) {
			intersection.hit = 0; // Outside the obj's caps
			return intersection;
		}

		intersection.norm = normalize(subtract(intersection.point, point_on_axis)); // Normal vector
	}

	return intersection;
}

t_intersection	intersect(t_ray ray, t_obj *obj)
{
	t_intersection intersection;

	intersection.hit = 0;
	intersection.distance = INFINITY;
	intersection.point = vec(0, 0, 0);
	intersection.norm = vec(0, 0, 0);

	// Call the specific intersection test based on the object type
	if (obj->type == SPHERE)
		return (intersect_sphere(ray, obj));
	else if (obj->type == CYLINDER)
		return (intersect_cylinder(ray, obj));
	else if (obj->type == PLANE)
		return (intersect_plane(ray, obj));
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
	int	i;

	closest_intersection.hit = 0;
	i = 0;
	while (i < world->object_num)
	{
		object = &world->obj[i];
		intersection = intersect(ray, object);
		if (intersection.hit)
		{
			if (intersection.distance < closest_distance)
			{
				closest_distance = intersection.distance;
				closest_intersection = intersection;
			}
		}
		i++;
	}

	return (closest_intersection);
}