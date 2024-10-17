#include "minirt.h"

void	loop(t_main *main)
{
	mlx_hook(main->win, 17, 0, close_window, main);
	mlx_loop(main->mlx);
}

t_ray	gen_ray(t_camera *cam, int x, int y)
{
	t_ray ray;
	double	aspect_ratio;
	double	pixel_x;
	double	pixel_y;

	aspect_ratio = cam->width / cam->height;
	
	pixel_x = (2 *((x + 0.5) / cam->width) - 1) * tan(cam->fov / 2 * PI / 180) * aspect_ratio;
	pixel_y = (1 - 2 * ((y + 0.5) / cam->height)) * tan(cam->fov / 2 * PI / 180);
	ray.origin = cam->pos;
	ray.dest = vec(pixel_x, pixel_y, 1);

	// ray.dest = vec_add(ray.origin, vec_cross(cam->norm, cam->direction));
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
		return (ret_color(184, 205, 255));
	/* else
		return (ret_color(20, 20, 100)); */
	// printf("Distance:%f\n", intersection.distance);
	incoming = intersection.emittance;
	new_ray.origin = intersection.point;
	new_ray.dest = vec_sub(ray.dest, vec_scalar(intersection.norm, 2 * vec_dot(ray.dest, intersection.norm)));


	incoming = trace_path(world, new_ray, depth + 1);
	return (color_scalar(color_add(intersection.emittance, incoming), (depth * 0.1)));
}

int	render(t_main *main, t_world *world)
{
	t_ray	ray;
	t_rgb	**output;
	int		output_color;
	int	pass;
	int	x;
	int	y;

	x = 0;
	y = 0;
	world->cam->direction = vec(0, 0, 1);
	output = (t_rgb **)calloc(world->cam->height + 1, sizeof(t_rgb *));
	while (y < world->cam->height)
	{
		output[y] = (t_rgb *)calloc(world->cam->width + 1, sizeof(t_rgb));
		y++;
	}
	pass = 1;
	y = 0;
	while (1)
	{
		while (y < main->height)
		{
			while (x < main->width)
			{
				ray = gen_ray(main->world->cam, x, y);
				// print_vec("initial ray", ray.origin);
				// print_vec(NULL, ray.dest);
				output[y][x] = color_scalar_div(color_add(output[y][x], trace_path(world, ray, 1)), pass);
				output_color = pack_color(output[y][x].r, output[y][x].g, output[y][x].b);
				mlx_pixel_put(main->mlx, main->win, x, y, output_color);
				x++;
			}
			x = 0;
			y++;
		}
		y = 0;
	}
	return (0);
}

int	main_pipeline(t_main *main)
{
	render(main, main->world);

	loop(main);
	return (0);
}