#include "minirt.h"

void	loop(t_main *main)
{
	mlx_hook(main->win, 17, 0, close_window, main);
	mlx_loop(main->mlx);
}

t_rgb	ret_color(int r, int g, int b)
{
	t_rgb	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

t_vec	cone_pewpew(t_vec norm, double angle)
{
	t_vec dir;

	double cone_angle_radians = angle * (PI / 180.0);

	// Generate random angles
	double random_phi = 2 * PI * ((double)ft_rand() / RAND_MAX);
	double random_theta = cone_angle_radians * ((double)ft_rand() / RAND_MAX);

	dir.x = sin(random_theta) * cos(random_phi);
	dir.y = sin(random_theta) * sin(random_phi);
	dir.z = cos(random_theta);
	
	if (norm.x >= 0)
		printf("pew\n");
		// printf("Don't forget to implement reflect function :)\n");
	return normalize(dir);
}

void print_vals(t_rgb incoming, t_ray new_ray, t_rgb emission)
{
	if (incoming.r > 0)
	{
		printf("emish:%i %i %i\n", emission.r, emission.g, emission.b);
		printf("incoming:%i %i %i\n", incoming.r, incoming.g, incoming.b);
		printf("new_ray.origin:%f %f %f\n", new_ray.origin.x, new_ray.origin.y, new_ray.origin.z);
		printf("new_ray.dest:%f %f %f\n", new_ray.dest.x, new_ray.dest.y, new_ray.dest.z);
	}
}

t_rgb	trace(t_ray ray, int depth, t_world *world)
{
	t_intersection	intersection;
	t_ray	new_ray;
	t_rgb	incoming;
	t_rgb	emission;
	// double	p;

	if (depth >= MAXDEPTH)
		return (ret_color(0, 0, 0));
	intersection = find_path(ray, world);
	printf("hit?: %i, distance: %f\n", intersection.hit, intersection.distance);
	if (!intersection.hit)
		return (ret_color(0, 0, 0));
	// continue from newray and get direction
	new_ray.origin = ray.dest;
	new_ray.dest = cone_pewpew(intersection.norm, 90);
	// incoming = ret_color(0, 0, 0);
	// p = 1 / (2 * PI);
	// implement BRDF

	emission = intersection.emittance;
	// Trace light source recursively
	incoming = trace(new_ray, depth + 1, world);

	print_vals(incoming, new_ray, emission);
	return (incoming);
}

t_rgb	raytrace(t_world *world, int x, int y)
{
	t_ray ray;
	int depth;

	// Generate ray: cone restricted to FOV!
	double aspect_ratio = (double)world->cam->width / (double)world->cam->height; // Image dimensions
	double fov_scale = tan(world->cam->fov / 2.0); // FOV in radians

	// Convert pixel indices to normalized device coordinates (NDC)
	double x_ndc = (2.0 * (double)x) / (double)world->cam->width - 1.0; // Normalized X
	double y_ndc = 1.0 - (2.0 * (double)y) / (double)world->cam->height; // Normalized Y, inverted

	// Adjust for aspect ratio
	x_ndc *= aspect_ratio;

	// Calculate ray direction using the camera's orientation and FOV
	t_vec ray_direction = vec(x_ndc * fov_scale, y_ndc * fov_scale, -1.0); // Assuming camera looks down -Z
	ray.origin = world->cam->pos; // Camera position
	ray.dest = add(ray.origin, ray_direction); // Calculate ray destination

	depth = 0;
	return trace(ray, depth, world);
	/* t_ray	ray;
	int		depth;

	// generate ray(cone restricted to fov!)
	ray.origin = add(world->cam->pos, vec((double)x,(double)y, 0.0));
	ray.dest = add(world->cam->norm, ray.origin);

	depth = 0;
	return (trace(ray, depth, world)); */
}

void	render(t_main *main, t_world *world)
{
	t_rgb	color;
	t_rgb	**screen;
	int	output;
	int	pass;
	int	x;
	int	y;

	pass = 0;
	x = 0;
	y = 0;
	screen = (t_rgb **)malloc(main->height * (sizeof(t_rgb *)));
	while (y < main->height)
	{
		screen[y] = (t_rgb *)malloc(main->width * (sizeof(t_rgb)));
		y++;
	}
	y = 0;
	printf("width and height: %i, %i\n", main->width, main->height);
	// generate rays for each pixel and incrementally add to pixel
	while (x < 3)
	{
		while (y < main->height)
		{
			while (x < main->width)
			{
				color = raytrace(world, y, x);
				screen[y][x] = color_add(screen[y][x], color);

				output = pack_color(screen[y][x].r, screen[y][x].g, screen[y][x].b);
				if (output > 0)
					printf("output: %i\n", output);
				/* if (pass > 0)
					output /= pass; */
				printf("pass:%i\n", pass);
				//	generate ray and save (to screen?)
				//	for now adding flat values over pixels
						// screen.color (use dot function) raytrace(world); // ???
				if (main->mlx)
					mlx_pixel_put(main->mlx, main->win, y, x, output);
				else
					printf("color to be put:%i\n", output);
				x++;
			}
			x = 0;
			y++;
		}
		y = 0;
		pass++;
	}
}

int	main_pipeline(t_main *main)
{
	render(main, main->world);

	loop(main);
	return (0);
}