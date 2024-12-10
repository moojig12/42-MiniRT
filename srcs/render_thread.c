/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmandakh <nmandakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:30:28 by fjoestin          #+#    #+#             */
/*   Updated: 2024/12/10 13:58:33 by nmandakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

	// The function for simulating and bouncing a ray off an object
t_rgb	trace_path(t_world *world, t_ray ray, int depth)
{
	t_intersect	intersection;
	t_rgb		return_color;
	t_rgb		incoming;
	t_ray		new_ray;
	double		brdf;

	return_color = ret_color(0, 0, 0);
	if (depth >= MAXDEPTH)
		return (return_color);
	intersection = find_path(ray, world);
	if (!intersection.hit)
		return (return_color);
	new_ray.origin = intersection.point;
	new_ray.dest = cone_pewpew(intersection.norm, &intersection.material, ray);
	brdf = brdf_calculation(intersection.material, new_ray, intersection.norm);
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
	t_thread_screen	screen;
	t_render		*thread;
	t_main			*main;
	t_rgb			**output;

	thread = (t_render *)arg;
	main = screen_init_thread(&screen, thread);
	output = main->output;
	while (screen.y < screen.y_limit)
	{
		while (screen.x < main->width)
		{
			thread_inner_render(main, output, screen.x, screen.y);
			screen.x++;
		}
		screen.x = 0;
		screen.y++;
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
	int			i;

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
