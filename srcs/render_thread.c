#include "minirt.h"

void	key_handles(t_main *main)
{
	mlx_key_hook(main->win, movement, main);
	mlx_hook(main->win, 17, 1L << 17, close_window, main);
}

	// The function for simulating and bouncing a ray off an object
t_rgb	trace_path(t_world *world, t_ray ray, int depth)
{
	t_intersection	intersection;
	t_rgb			return_color;
	t_rgb			incoming;
	t_ray			new_ray;
	double			brdf;

	return_color = ret_color(0, 0, 0);
	if (depth >= MAXDEPTH)
		return (return_color);
	intersection = find_path(ray, world);
	if (!intersection.hit)
		return (world->amb->color);
	new_ray.origin = intersection.point;
	new_ray.dest = cone_pewpew(intersection.norm, intersection, ray);
	brdf = brdf_calculation(intersection, new_ray, intersection.norm);
	incoming = trace_path(world, new_ray, depth + 1);
	return_color = color_scalar(color_multiply(world->amb->color, \
	intersection.color), world->amb->ratio);
	return_color = direct_light_occlusion(intersection, world, return_color);
	return_color = color_add(return_color, color_scalar(incoming, brdf));
	return (color_normalize(return_color));
}

// Main function for rendering the screen for each frame called by mlx_loop_hook
void	*render_thread(void *arg)
{
	t_render	*thread;
	t_main		*main;
	t_rgb		**output;
	int			output_color;
	int			x;
	int			y;
	int			y_limit;

	thread = (t_render *)arg;
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
	while (y < y_limit)
	{
		while (x < main->width)
		{
			if (main->render_switch == HIGH)
				render_super(main, x, y, output);
			else
				render_low(main, x, y, output);
			output_color = pack_color(output[y][x]);
			if (main->render_switch == LOW)
				output[y][x] = ret_color(0, 0, 0);
			put_pixel_to_img(output_color, *main, x, y);
			x++;
		}
		x = 0;
		y++;
	}
	if (pthread_mutex_trylock(thread->write_lock) == 0)
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
		pthread_create(&threads[i].thread, NULL, &render_thread, \
		(void *)&threads[i]);
		i++;
	}
	i = 0;
	while (i < THREAD_COUNT)
	{
		pthread_join(threads[i].thread, NULL);
		i++;
	}
	return (0);
}

void	initiate_mutexes(t_main *main)
{
	int	y;

	y = 0;
	main->thread = malloc(THREAD_COUNT * sizeof(t_render));
	pthread_mutex_init(&main->write_lock, NULL);
	main->output_pixel = (pthread_mutex_t *)malloc(main->height \
	* sizeof(pthread_mutex_t));
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
	if (!XInitThreads())
	{
		fprintf(stderr, "Failed to initialize Xlib threads\n");
		return (EXIT_FAILURE);
	}
	initiate_mutexes(main);
	mlx_loop_hook(main->mlx, render_thread_wrapper, main);
	key_handles(main);
	mlx_loop(main->mlx);
	return (0);
}
