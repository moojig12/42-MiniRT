#include "minirt.h"

void	key_handles(t_main *main)
{
	mlx_key_hook(main->win, movement, main);
	mlx_hook(main->win, 17, 0, close_window, main);
}

/* t_vec	cone_pewpew(t_vec norm, double angle)
{
	t_vec dir;

	double cone_angle_radians = angle * (PI / 180.0);

	// Generate random angles
	double random_phi = 2 * PI * ((double)ft_rand() / RAND_MAX);
	double random_theta = cone_angle_radians * ((double)ft_rand() / RAND_MAX);

	dir.x = sin(random_theta) * cos(random_phi);
	dir.y = sin(random_theta) * sin(random_phi);
	dir.z = cos(random_theta);

	return vec_normalize(dir);
} */

t_ray	gen_ray(t_camera *cam, int x, int y)
{
	t_ray ray;
	double	aspect_ratio;
	double	pixel_x;
	double	pixel_y;
	double	jitter_x = random_double_range(-0.5, 0.5);
	double	jitter_y = random_double_range(-0.5, 0.5);

	aspect_ratio = cam->width / cam->height;
	
	pixel_x = (2 *((x + 0.5 + jitter_x) / cam->width) - 1) * tan(cam->fov / 2 * PI / 180) * aspect_ratio;
	pixel_y = (1 - 2 * ((y + 0.5 + jitter_y) / cam->height)) * tan(cam->fov / 2 * PI / 180);

	// Create the camera basis: right, up, and forward
	t_vec forward = vec_normalize(cam->direction);
	t_vec right = vec_normalize(vec_cross(cam->norm, forward));
	t_vec up = vec_cross(forward, right);

	/* ray.origin = cam->pos;
	ray.dest = vec(pixel_x, pixel_y, 1); */

	ray.origin = cam->pos;
	ray.dest = vec_add(vec_add(vec_scalar(right, pixel_x), vec_scalar(up, pixel_y)), vec_scalar(forward, 1));
	ray.dest = vec_normalize(ray.dest);

	// ray.norm = cam->norm;

	return (ray);
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
		return (world->amb->color);

	new_ray.origin = intersection.point;
	new_ray.dest = vec_sub(ray.dest, vec_scalar(intersection.norm, 2 * vec_dot(ray.dest, intersection.norm)));
	// new_ray.norm = intersection.norm;

	double	cos_theta = vec_dot(new_ray.dest, intersection.norm);
	double	BRDF = (1.0 / PI);

	incoming = trace_path(world, new_ray, depth + 1);
	t_rgb	return_color = color_add(intersection.emittance, color_scalar(color_scalar(incoming, cos_theta), BRDF));
	return_color = color_add(return_color, color_scalar(world->amb->color, world->amb->ratio));
	return (color_normalize(return_color));
}

int	render(t_main *main)
{
	t_ray	ray;
	t_rgb	**output;
	t_world	*world;
	int		output_color;
	int		x;
	int		y;

	output = main->output;
	world = main->world;
	x = 0;
	y = 0;
	while (y < main->height)
	{
		while (x < main->width)
		{
			ray = gen_ray(main->world->cam, x, y);
			output[y][x] = color_add(output[y][x], trace_path(world, ray, 1));
			output_color = pack_color(output[y][x].r, output[y][x].g, output[y][x].b);
			mlx_pixel_put(main->mlx, main->win, x, y, output_color);
			output[y][x] = ret_color(0, 0, 0);
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

int	main_pipeline(t_main *main)
{
	mlx_loop_hook(main->mlx, render, main);
	key_handles(main);
	mlx_loop(main->mlx);
	return (0);
}