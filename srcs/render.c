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
		printf("Don't forget to implement reflect function :)\n");
	return normalize(dir);
}

void print_vals(t_obj *last_object, t_rgb BRDF, t_rgb incoming, t_ray new_ray, t_rgb emission)
{
	if (last_object)
	{
		printf("object exists!\n");
		// printf("Type:%i\n", last_object->type);
	}
	printf("BRDF\n r:%i g:%i b:%i\n", BRDF.r, BRDF.g, BRDF.b);
	printf("new ray origin\n x:%f y:%f z:%f\n", new_ray.origin.x, new_ray.origin.y, new_ray.origin.z);
	printf("new ray dest\n x:%f y:%f z:%f\n", new_ray.dest.x, new_ray.dest.y, new_ray.dest.z);
	printf("incoming\n r:%i g:%i b:%i\n", incoming.r, incoming.g, incoming.b);
	printf("emission\n r:%i g:%i b:%i\n", emission.r, emission.g, emission.b);
}

t_rgb	trace(t_ray ray, int depth, t_world *world, t_obj *last_object)
{
	t_intersection	intersection;
	t_ray	new_ray;
	t_rgb	incoming;
	t_rgb	emission;
	t_rgb	BRDF;
	double	p;

	if (depth >= MAXDEPTH)
		return (ret_color(0, 0, 0));
	intersection = find_path(ray, world);
	if (!intersection.hit)
		return (ret_color(0, 0, 0));
	// continue from newray and get direction
	new_ray.origin = ray.dest;
	new_ray.dest = cone_pewpew(intersection.norm, 90);

	p = 1 / (2 * PI);
	// implement BRDF
	if (last_object != NULL)
	{
		// emission = last_object->material.emission;
		emission = world->amb->color;
		// BRDF = BRDF_lambertan(last_object->material.reflectance);
		BRDF = ret_color(0, 0, 0);
	}
	else
	{
		// emission = ret_color(0, 0, 0);
		emission = world->amb->color;
		BRDF = ret_color(0, 0, 0);
	}
	// Trace light source recursively
	incoming = trace(new_ray, depth + 1, world, intersection.obj);
	print_vals(last_object, BRDF, incoming, new_ray, emission);
	if (last_object)
		return (color_add(emission, (color_multiply(BRDF, (color_scalar(incoming, dot(last_object->norm, new_ray.origin) / p))))));
	else
		return (color_add(emission, (color_multiply(BRDF, (color_scalar(incoming, dot(vec(0, 0, 0), new_ray.origin) / p))))));
}

t_rgb	raytrace(t_world *world, int x, int y)
{
	t_ray	ray;
	int		depth;
	t_obj	*fake_obj;

	// generate ray(cone restricted to fov!)
	ray.origin = add(world->cam->pos, vec((double)x,(double)y, 0.0));
	ray.dest = add(world->cam->norm, ray.origin);

	fake_obj = malloc(sizeof(t_obj));
	depth = 0;
	fake_obj->type = 1;
	fake_obj->pos = vec(x, y, 0);
	fake_obj->norm = vec(0, 0, 0);
	fake_obj->material.reflectance = ret_color(0, 0, 0);
	fake_obj->material.color = ret_color(0, 0, 0);
	fake_obj->material.emission = ret_color(0, 0, 0);
	return (trace(ray, depth, world, fake_obj));
}

void	render(t_main *main, t_world *world)
{
	t_rgb	color;
	t_rgb	accumilation;
	int	i;
	int	j;

	i = 0;
	j = 0;
	accumilation = ret_color(0, 0, 0);
	printf("height and width: %i, %i\n", main->height, main->width);
	// generate rays for each pixel and incrementally add to pixel
	while (1)
	{
		while (j < main->height)
		{
			while (i < main->width)
			{
				color = raytrace(world, i, j);
				accumilation = color_add(accumilation, color);
				//	generate ray and save (to screen?)
				//	for now adding flat values over pixels
						// screen.color (use dot function) raytrace(world); // ???
				mlx_pixel_put(main->mlx, main->win, i, j, pack_color(accumilation.r, accumilation.g, accumilation.b));
				i++;
			}
			i = 0;
			j++;
		}
		j = 0;
	}
}

int	main_pipeline(t_main *main)
{
	render(main, main->world);

	loop(main);
	return (0);
}