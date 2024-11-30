#include "minirt.h"


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
	double	magnitude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

	if (magnitude == 0)
		return (t_vec){0, 0, 0, 0};

	return (t_vec){v.x / magnitude, v.y / magnitude, v.z / magnitude, 1};
}
