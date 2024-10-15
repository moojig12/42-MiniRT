#include "minirt.h"

void	loop(t_main *main)
{
	mlx_hook(main->win, 17, 0, close_window, main);
	mlx_loop(main->mlx);
}

t_ray	gen_ray(t_camera *cam, int x, int y)
{
	t_ray ray;
	double aspect_ratio = (double)cam->width / (double)cam->height;
	double tan_fov_over_2 = tan((cam->fov * 0.5) * (M_PI / 180.0)); // Convert FOV to radians

	// Calculate normalized device coordinates
	double ndc_x = (x + 0.5) / cam->width; // Add 0.5 for the center of the pixel
	double ndc_y = (y + 0.5) / cam->height;

	// Convert NDC to view space coordinates
	double screen_x = (2.0 * ndc_x - 1.0) * aspect_ratio * tan_fov_over_2;
	double screen_y = (1.0 - 2.0 * ndc_y) * tan_fov_over_2;

	// Define ray direction as a vector from the camera's position
	t_vec ray_direction = {screen_x, screen_y, -1.0}; // Assuming camera looks down -Z axis
	ray_direction = vec_normalize(ray_direction); // Normalize the direction

	// Set the ray origin and direction
	ray.origin.x = x;
	ray.origin.y = y;
	ray.origin.z = cam->pos.z; // Set the origin to the camera's position
	ray.dest = ray_direction; // Set the direction

	// Optional: Print debug info for ray origin and direction
	printf("Ray Origin: (%f, %f, %f), Ray Direction: (%f, %f, %f)\n",
		ray.origin.x, ray.origin.y, ray.origin.z,
		ray_direction.x, ray_direction.y, ray_direction.z);

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
	
	incoming = intersection.emittance;
	new_ray.origin = intersection.point;

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
	while (y < main->height)
	{
		while (x < main->width)
		{
			// ray = gen_ray(main->world->cam, x, y);
			ray.origin = vec(world->cam->pos.x + x, world->cam->pos.y + y, world->cam->pos.z);
			ray.dest = vec_normalize(vec_add(ray.origin, vec_cross(world->cam->norm, vec(0, 0, 1))));
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
	return (0);
}

int	main_pipeline(t_main *main)
{
	render(main, main->world);

	loop(main);
	return (0);
}