#include "minirt.h"

void	key_handles(t_main *main)
{
	mlx_key_hook(main->win, movement, main);
	mlx_hook(main->win, 17, 1L<<17, close_window, main);
}

t_vec	cone_pewpew(t_vec norm)
{
	t_vec dir;

	dir = random_vec(0);

	if (vec_dot(dir, norm) < 0)
		dir = vec_scalar(dir, -1);

	return vec_normalize(dir);
}

t_ray	gen_ray(t_camera *cam, int x, int y)
{
	t_ray ray;
	double	aspect_ratio;
	double	pixel_x;
	double	pixel_y;
	double	jitter_x = random_double_range(-0.005, 0.005);
	double	jitter_y = random_double_range(-0.005, 0.005);

	aspect_ratio = (cam->width / cam->height);
	
	// Normalized Device Coordinates
	double	ndc_x = (x + 0.5 ) / cam->width;
	double	ndc_y = (y + 0.5 ) / cam->height;

	pixel_x = (2 * ndc_x - 1 + jitter_x) * tan(cam->fov * 0.5 * PI / 180) * aspect_ratio;
	pixel_y = (1 - 2 * ndc_y + jitter_y) * tan(cam->fov * 0.5 * PI / 180);

	// Create the camera basis: right, up, and forward
	t_vec forward = vec_normalize(cam->direction);
	t_vec right = vec_normalize(vec_cross(cam->norm, forward));
	t_vec up = vec_cross(forward, right);

	ray.origin = cam->pos;
	ray.dest = vec_add(vec_add(vec_scalar(right, pixel_x), vec_scalar(up, pixel_y)), vec_scalar(forward, 1));
	ray.dest = vec_normalize(ray.dest);

	return (ray);
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
	diffuse = intersection.diffuse * fmax(0.0, cos_theta);

	// Specular component (e.g., Cook-Torrance model)
	specular = fresnel * intersection.specular;

	return (diffuse + specular);
}

	// The function for simulating and bouncing a ray off an object
t_rgb	trace_path(t_world *world, t_ray ray, int depth)
{
	t_intersection	intersection;
	t_rgb	return_color;
	t_rgb	incoming;
	t_ray	new_ray;

	return_color = ret_color(0, 0, 0);
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
	double	p = 1;
		// Shoot the next ray recursively
	incoming = trace_path(world, new_ray, depth + 1);

		// Ambience
	return_color = color_multiply(world->amb->color, intersection.color);
	return_color = color_scalar(return_color, world->amb->ratio);

		// Calculate light position and shadow
		t_ray shadow_ray;

		shadow_ray.origin = intersection.point;
		shadow_ray.dest = vec_normalize(vec_sub(world->light->pos, intersection.point));
		// shadow_ray.dest = cone_pewpew(intersection.norm);
		if (!find_path(shadow_ray, world).hit) {
			double light_d =  vec_length(vec_sub(world->light->pos, intersection.point));
			double attenuation = 1.0 / (light_d * light_d); // Inverse square law
			double cos_theta_s = fmax(0.0, vec_dot(intersection.norm, shadow_ray.dest));
			t_rgb light_contribution = color_scalar(color_multiply(world->light->color, intersection.color), cos_theta_s * attenuation * world->light->brightness);
			return_color = color_add(return_color, light_contribution);
		}
		// Indirect lighting
			// Adding the color return of the recursively shot ray and adding up the values then scaling with BRDF
	return_color = color_add(return_color, color_scalar(color_scalar(incoming, 1.5), BRDF * p));


	return (color_normalize(return_color));
}


// Main function for rendering the screen for each frame called by mlx_loop_hook
int	render(t_main *main)
{
	static int	static_sample = 2;
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
			// Initializes the position of the first ray from the camera to static_sample into trace_path later
				// sampleses in trace_path function to shoot rays and get the result of the ray bounces back
			for (int i = 0; i < static_sample; i++)
				output[y][x] = color_add(output[y][x], trace_path(world, ray, 1));
			output[y][x] = color_scalar_div(output[y][x], static_sample);


			// Packs color into ARGB format for mlx_pixel_put
			output_color = pack_color(output[y][x].r, output[y][x].g, output[y][x].b);
			mlx_pixel_put(main->mlx, main->win, x, y, output_color);

			// Refreshing to screen to black
			// output[y][x] = ret_color(0, 0, 0);
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

int	main_pipeline(t_main *main)
{
	// Call render() function each frame with mlx_loop while handling input
	mlx_loop_hook(main->mlx, render, main);

	// Take input
	key_handles(main);
	mlx_loop(main->mlx);
	return (0);
}