#include "minirt.h"

void	calc_projection(t_ray ray, t_comp *comp, t_cyl *cyl, t_intersect *inter)
{
	double	projection1;
	double	projection2;

	inter->distance = comp->t;
	inter->point = vec_add(ray.origin, vec_scalar(ray.dest, comp->t));
	projection1 = vec_dot(vec_sub(vec_add(ray.origin, vec_scalar(ray.dest, comp->t1)), cyl->pos), comp->axis);
	if (comp->t1 > 0 && projection1 >= 0.0001 && projection1 <= cyl->height)
	{
		comp->t = comp->t1;
		inter->hit = 1;
	}
	projection2 = vec_dot(vec_sub(vec_add(ray.origin, vec_scalar(ray.dest, comp->t2)), cyl->pos), comp->axis);
	if ((!inter->hit || comp->t2 < comp->t) && comp->t2 > 0 && projection2 >= 0.0001 && projection2 <= cyl->height)
	{
		comp->t = comp->t2;
		inter->hit = 1;
	}
}

void	pop_intersec_cyl(t_ray ray, t_intersect *inter, t_comp comp, t_cyl *cyl)
{
	t_vec	point_on_axis;
	double	projection;

	inter->distance = comp.t;
	inter->point = vec_add(ray.origin, vec_scalar(ray.dest, comp.t));
	projection = vec_dot(vec_sub(inter->point, cyl->pos), comp.axis);
	point_on_axis = vec_add(cyl->pos, vec_scalar(comp.axis, projection));
	inter->norm = vec_normalize(vec_sub(inter->point, point_on_axis));
	inter->color = cyl->color;
}