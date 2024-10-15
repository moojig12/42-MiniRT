#include "minirt.h"

void	loop(t_main *main)
{
	mlx_hook(main->win, 17, 0, close_window, main);
	mlx_loop(main->mlx);
}

t_ray	gen_ray(t_camera *cam, int x, int y)
{
	t_ray ray;

	ray.origin = vec(cam->pos.x + x, cam->pos.y + y, cam->pos.z);
	ray.dest = vec_add(ray.origin, vec_cross(cam->norm, vec(0, 0, 1)));
	return ray;
}

t_rgb	trace_path(t_world *world, t_ray ray, int depth)
{
	t_rgb	incoming;
	t_ray	new_ray;
	t_intersection	intersection;

	if (depth >= MAXDEPTH)
		return (ret_color(0, 0, 0));

	intersection = find_path(ray, world);
	if (intersection.hit == 0)
		return (ret_color(0, 0, 0));
	printf("Distance:%f\n", intersection.distance);
	incoming = intersection.emittance;
	new_ray.origin = intersection.point;
	new_ray.dest = vec_cross(new_ray.origin, intersection.norm);

	trace_path(world, new_ray, depth + 1);
	return (color_scalar(incoming, (depth * 0.1)));
}

int	render(t_main *main, t_world *world)
{
	t_ray	ray;
	t_rgb	output;
	int		output_color;
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (1)
	{
		while (y < main->height)
		{
			while (x < main->width)
			{
				ray = gen_ray(main->world->cam, x, y);
				print_vec("initial ray", ray.origin);
				print_vec(NULL, ray.dest);
				/* printf("ray direction and origin\ndir: %f %f %f\norigin: %f %f %f\n", \
				ray.dest.x, ray.dest.y, ray.dest.z, ray.origin.x, ray.origin.y, ray.origin.z); */
				output = trace_path(world, ray, 1);
				output_color = pack_color(output.r, output.g, output.b);
				mlx_pixel_put(main->mlx, main->win, x, y, output_color);
				x++;
			}
			x = 0;
			y++;
		}
	}
	return (0);
}

int	main_pipeline(t_main *main)
{
	render(main, main->world);

	loop(main);
	return (0);
}