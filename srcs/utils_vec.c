#include "minirt.h"

t_vec	vec(double x, double y, double z, double w)
{
	t_vec	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	vec.w = w;
	return (vec);
}

t_vec vec_add(t_vec a, t_vec b)
{
	t_vec ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	return (ret);
}

t_vec	vec_sub(t_vec a, t_vec b)
{
	t_vec ret;

	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return (ret);
}

double	vec_dot(t_vec a, t_vec b)
{
	double ret;

	ret = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	return (ret);
}

t_vec	vec_cross(t_vec a, t_vec b)
{
	t_vec	ret;

	ret.x = a.y * b.z - a.z * b.y;
	ret.y = a.z * b.x - a.x * b.z;
	ret.z = a.x * b.y - a.y * b.x;

	return (ret);
}

double vec_length(t_vec v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vec	vec_scalar(t_vec a, double b)
{
	t_vec ret;

	ret.x = a.x * b;
	ret.y = a.y * b;
	ret.z = a.z * b;

	return (ret);
}

t_vec	vec_normalize(t_vec v)
{
	double magnitude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

	// Check to avoid division by zero
	if (magnitude == 0) {
		// Return a zero vector or handle this case as needed
		return (t_vec){0, 0, 0};
	}

	// Divide each component by the magnitude to normalize
	return (t_vec){v.x / magnitude, v.y / magnitude, v.z / magnitude};
}