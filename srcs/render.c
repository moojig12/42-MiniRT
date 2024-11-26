#include "../minirt.h"

void	key_handles(t_main *main)
{
	mlx_key_hook(main->win, movement, main);
	mlx_hook(main->win, 17, 1L<<17, close_window, main);
}

t_vec	cone_pewpew(t_vec norm)
{
	t_vec dir;

	dir = random_vec(0);

	// dir = vec_normalize(vec_add(dir, vec_scalar(norm, 1)));
	if (vec_dot(dir, norm) < 0)
		dir = vec_scalar(dir, -1);

	return vec_normalize(dir);
}

	// BRDF calculation for materials, not sure if it works 100% yet
double	brdf_calculation(t_intersection intersection, t_ray ray, t_vec norm)
{
	double	fresnel;
	double	diffuse;
	double	specular;
	double	cos_theta = vec_dot(ray.dest, norm);

	 // Fresnel reflectance (e.g., Schlick's approximation)
	fresnel = intersection.reflectance + (1 - intersection.reflectance) * pow(1 - cos_theta, 5);

	// Diffuse component
	diffuse = intersection.diffuse * cos_theta;

	// Specular component (e.g., Cook-Torrance model)
	specular = fresnel * intersection.specular;

	return (diffuse + specular);
}

t_rgb	direct_light_occlusion(t_intersection intersection, t_world *world, t_rgb return_color)
{
	t_ray shadow_ray;
	double	attenuation;
	double	light_distance;
	double	cos_theta;

	shadow_ray.origin = vec_add(intersection.point, vec_scalar(intersection.norm, EPSILON));
	shadow_ray.dest = vec_normalize(vec_sub(world->light->pos, shadow_ray.origin));
	light_distance =  vec_length(vec_sub(world->light->pos, intersection.point));
	if (!is_occluded(shadow_ray, world, light_distance)) {
		attenuation = 1.0 / (light_distance * light_distance);
		cos_theta = vec_dot(intersection.norm, shadow_ray.dest);
		t_rgb light_contribution = color_scalar(color_multiply(world->light->color, intersection.color), cos_theta * attenuation * world->light->brightness);
		return_color = color_add(return_color, light_contribution);
	}
	return (color_normalize(return_color));
}

	// The function for simulating and bouncing a ray off an object
t_rgb	trace_path(t_world *world, t_ray ray, int depth)
{
	t_intersection	intersection;
	t_rgb	return_color;
	t_rgb	incoming;
	t_ray	new_ray;

	return_color = ret_color(0.0, 0.0, 0.0);
	if (depth >= MAXDEPTH)
		return (return_color);

		// Iterate over each object in the world and find the closest intersection.
			// Also fetches data relating to the object such as Material and Norm direction
	intersection = find_path(ray, world);
	if (!intersection.hit)
		return (return_color);
		// return	(world->amb->color);

		// initialize a new ray from the POINT of Intersection and random direction
	new_ray.origin = intersection.point;
		// Shoots random rays in possible direction
	new_ray.dest = cone_pewpew(intersection.norm);
	// new_ray.dest = vec_sub(ray.dest, vec_scalar(intersection.norm, 2 * vec_dot(ray.dest, intersection.norm)));

		// Calculations i found off the internet for BRDF
	// double	cos_theta = vec_dot(new_ray.dest, intersection.norm);
	double	BRDF = brdf_calculation(intersection, new_ray, intersection.norm);
	double	p = 1.0 / (PI);
		// Shoot the next ray recursively
	incoming = trace_path(world, new_ray, depth + 1);
		// Ambience
	return_color = color_multiply(world->amb->color, intersection.color);
	return_color = color_scalar(return_color, world->amb->ratio);
		// Calculate light position and shadow
	return_color = direct_light_occlusion(intersection, world, return_color);
		// Indirect lighting
			// Adding the color return of the recursively shot ray and adding up the values then scaling with BRDF
	return_color = color_add(return_color, color_scalar(color_scalar(incoming, 1), BRDF * p));


	return (color_normalize(return_color));
}

void	render_super(t_main *main, int x, int y, t_rgb **output)
{
	t_ray	ray;
	double	offset_x;
	double	offset_y;

	for (int sub_y = 0; sub_y < STATIC_SAMPLE; sub_y++)
	{
		for (int sub_x = 0; sub_x < STATIC_SAMPLE; sub_x++)
		{
				// Offset for each subpixel
			offset_x = (sub_x) / STATIC_SAMPLE;
			offset_y = (sub_y) / STATIC_SAMPLE;
				// Initliaze individual sub_ray to pass into trace_path and average later on
			ray = gen_ray(main->world->cam, x + offset_x, y + offset_y);
			output[y][x] = color_add(output[y][x], trace_path(main->world, ray, 1));
		}
	}
		// Average the samples
	output[y][x] = color_scalar_div(output[y][x], STATIC_SAMPLE * STATIC_SAMPLE);
	output[y][x] = color_normalize(output[y][x]);
}

void	render_low(t_main *main, int x, int y, t_rgb **output)
{
	t_ray	ray;

	ray = gen_ray_low(main->world->cam, x, y);
	output[y][x] = color_add(output[y][x], trace_path(main->world, ray, 1));
	output[y][x] = color_normalize(output[y][x]);
}

// Main function for rendering the screen for each frame called by mlx_loop_hook
int	render(t_main *main)
{
	t_rgb	**output;
	int		output_color;
	int		x;
	int		y;

	output = main->output;
	x = 0;
	y = 0;
	trace_time(1);
	while (y < main->height)
	{
		while (x < main->width)
		{
			if (main->render_switch == HIGH)
				render_super(main, x, y, output);
			else
				render_low(main, x, y, output);
			// Packs color into ARGB format for mlx_pixel_put
			output_color = pack_color(output[y][x]);
			if (main->render_switch == LOW)
				output[y][x] = ret_color(0, 0, 0);
			mlx_pixel_put(main->mlx, main->win, x, y, output_color);
			x++;
		}
		x = 0;
		y++;
	}
	trace_time(2);
	return (0);
}

int	main_pipeline(t_main *main)
{
	// Take input
	key_handles(main);
	// Call render() function each frame with mlx_loop while handling input
	mlx_loop_hook(main->mlx, render, main);
	mlx_loop(main->mlx);
	return (0);
}