#include "minirt.h"

void	key_handles(t_main *main)
{
	mlx_key_hook(main->win, movement, main);
	mlx_hook(main->win, 17, 1L<<17, close_window, main);
}

t_vec	cone_pewpew(t_vec norm, double diffuse)
{
	t_vec	return_dir;
	t_vec	dir;

	dir = random_vec(0);

	// dir = vec_normalize(vec_add(dir, vec_scalar(norm, 1)));
	if (vec_dot(dir, norm) < 0)
		dir = vec_scalar(dir, -1);

	// Interpolate between the normal and the random direction based on diffuse
	return_dir = vec_add(
		vec_scalar(norm, 1.0 - diffuse),      // Normal contribution (tighter cone for lower diffuse)
		vec_scalar(dir, diffuse)      // Random contribution (wider cone for higher diffuse)
	);
	return vec_normalize(return_dir);
}

double	brdf_calculation(t_intersection intersection, t_ray ray, t_vec norm)
{
	double	fresnel;
	double	diffuse;
	double	specular;
	double	cos_theta = vec_dot(ray.dest, norm);

	 // Fresnel reflectance (e.g., Schlick's approximation)
	fresnel = intersection.reflectance + (1 - intersection.reflectance) * pow(1.0 - cos_theta, 5.0);

	// Diffuse component
	diffuse = intersection.diffuse * cos_theta;

	// Specular component (e.g., Cook-Torrance model)
	specular = fresnel * intersection.specular;

	return (diffuse + specular);
}

t_rgb	direct_light_occlusion(t_intersection intersection, t_world *world, t_rgb return_color)
{
	t_ray shadow_ray;
	t_rgb	light_contribution;
	double	attenuation;
	double	light_distance;
	double	cos_theta;
	double	BRDF;

	shadow_ray.origin = vec_add(intersection.point, vec_scalar(intersection.norm, EPSILON));
	shadow_ray.dest = vec_normalize(vec_sub(world->light->pos, shadow_ray.origin));
	light_distance =  vec_length(vec_sub(world->light->pos, intersection.point));
	if (!is_occluded(shadow_ray, world, light_distance)) {
		attenuation = 1.0 / (light_distance * light_distance);
		cos_theta = vec_dot(intersection.norm, shadow_ray.dest);
		cos_theta = fmax(0.0, cos_theta);
		BRDF = brdf_calculation(intersection, shadow_ray, intersection.norm) / PI;
		light_contribution = color_scalar(color_multiply(world->light->color, intersection.color), cos_theta * attenuation * world->light->brightness * BRDF);
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
	double	p;
	double	BRDF;

	return_color = ret_color(0, 0, 0);
	if (depth >= MAXDEPTH)
		return (color_scalar(world->amb->color, world->amb->ratio));

		// Iterate over each object in the world and find the closest intersection.
			// Also fetches data relating to the object such as Material and Norm direction
	intersection = find_path(ray, world);
	if (!intersection.hit)
		return (color_scalar(world->amb->color, world->amb->ratio));
		// return	(world->amb->color);

		// initialize a new ray from the POINT of Intersection and random direction
	new_ray.origin = intersection.point;
		// Shoots random rays in possible direction
	// new_ray.dest = cone_pewpew(intersection.norm);

		// Generate a random direction (diffuse component)
	new_ray.dest = cone_pewpew(intersection.norm, intersection.diffuse);
		// BRDF
	BRDF = brdf_calculation(intersection, new_ray, intersection.norm);
	p = 1.0 / (PI);
		// Shoot the next ray recursively
	incoming = trace_path(world, new_ray, depth + 1);
		// Ambience
	return_color = color_multiply(world->amb->color, intersection.color);
	return_color = color_scalar(return_color, world->amb->ratio);
		// Direct lighting
	return_color = direct_light_occlusion(intersection, world, return_color);
		// Indirect lighting
	return_color = color_add(return_color, color_scalar(incoming, BRDF * p));


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

void	put_pixel_to_img(int color, t_main main, int x, int y)
{
	char	*pxl;

	if (x >= 0 && x < main.width && y >= 0 && y < main.height)
	{
		pxl = main.addr + (y * main.line_length + x *(main.bits_per_pixel / 8));
		*(unsigned int*)pxl = color;
	}
	
}

// Main function for rendering the screen for each frame called by mlx_loop_hook
void	*render(void *arg)
{
	t_render	*thread;
	t_main	*main;
	t_rgb	**output;
	// pthread_mutex_t	*render_lock;
	int		output_color;
	int		x;
	int		y;
	int		y_limit;

	thread = (t_render *)arg;
	// render_lock = thread->render_lock;
	main = thread->main;
	output = main->output;
	x = 0;
	y = 0;
	y_limit = main->height / THREAD_COUNT;
	if (thread->id != 1)
	{
		y = 0 + (main->height / thread->id);
		y_limit = (y_limit * thread->id);
	}
	// trace_time(1);
	while (y < y_limit)
	{
		/* if (pthread_mutex_trylock(&render_lock[y]) != 0)
		{ */
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
				put_pixel_to_img(output_color, *main, x, y);
				//mlx_pixel_put(main->mlx, main->win, x, y, output_color);
				x++;
			}
			/* pthread_mutex_unlock(&render_lock[y]);
		} */
		x = 0;
		y++;
	}
	// printf("thread id: %i\n", thread->id);
	// trace_time(2);
	if (pthread_mutex_lock(thread->write_lock) == 0)
	{
		mlx_put_image_to_window(main->mlx, main->win, main->img, 0, 0);
		pthread_mutex_unlock(thread->write_lock);
	}
	return (NULL);
}

int	render_thread_wrapper(t_main *main)
{
	t_render	*threads;
	int	i;

	i = 0;
	threads = main->thread;
	while (i < THREAD_COUNT)
	{
		pthread_create(&threads[i].thread, NULL, &render, (void *)&threads[i]);
		i++;
	}
	for (int j = 0; j < THREAD_COUNT; j++)
		pthread_join(threads[j].thread, NULL);
	return (0);
}

void	initiate_mutexes(t_main *main)
{
	int y = 0;

	main->thread = malloc(THREAD_COUNT * sizeof(t_render));
	pthread_mutex_init(&main->write_lock, NULL);
	main->output_pixel = (pthread_mutex_t *)malloc(main->height * sizeof(pthread_mutex_t));
	while (y < THREAD_COUNT)
	{
		pthread_mutex_init(&main->output_pixel[y], NULL);
		main->thread[y].id = y + 1;
		main->thread[y].main = main;
		main->thread[y].world = main->world;
		main->thread[y].image_ptr = main->img;
		main->thread[y].render_lock = main->output_pixel;
		main->thread[y].write_lock = &main->write_lock;
		y++;
	}
}

int	main_pipeline(t_main *main)
{
	if (!XInitThreads()) {
		fprintf(stderr, "Failed to initialize Xlib threads\n");
		return (EXIT_FAILURE);
	}

	initiate_mutexes(main);
	// Take input
	// Call render() function each frame with mlx_loop while handling input
	mlx_loop_hook(main->mlx, render_thread_wrapper, main);
	//render(main);
	//mlx_put_image_to_window(main->mlx, main->win, main->img, 0, 0);
	key_handles(main);
	mlx_loop(main->mlx);
	return (0);
}