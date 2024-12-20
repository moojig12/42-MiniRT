/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmandakh <nmandakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:30:24 by fjoestin          #+#    #+#             */
/*   Updated: 2024/12/20 15:23:52 by nmandakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

	// The function for simulating and bouncing a ray off an object
t_rgb	trace_path(t_world *world, t_ray ray, int depth)
{
	t_intersect		intersection;
	t_rgb			color;
	t_rgb			incoming;
	t_ray			new_ray;
	double			brdf;

	color = ret_color(0, 0, 0);
	if (depth >= MAXDEPTH)
		return (color);
	intersection = find_path(ray, world);
	if (!intersection.hit)
		return (color);
	new_ray.origin = intersection.point;
	new_ray.dest = cone_pewpew(intersection.norm, &intersection.material, ray);
	brdf = brdf_calculation(intersection.material, new_ray, intersection.norm);
	incoming = trace_path(world, new_ray, depth + 1);
	color = color_multiply(world->amb->color, intersection.color);
	color = color_scalar(color, world->amb->ratio);
	if (world->light)
		color = direct_light_occlusion(intersection, \
		world, color);
	color = color_add(color, color_scalar(incoming, brdf * (1 / PI)));
	color = color_add(color, \
	color_scalar(ret_color(1.0, 1.0, 1.0), intersection.emission));
	return (color_normalize(color));
}

// Main function for rendering the screen for each frame called by mlx_loop_hook
int	render(t_main *main)
{
	t_rgb	**output;
	int		x;
	int		y;

	output = main->output;
	x = 0;
	y = 0;
	while (y < main->height)
	{
		while (x < main->width)
		{
			if (main->render_switch == HIGH)
				render_super(main, x, y, output);
			else
				render_low(main, x, y, output);
			put_color_to_buff(main, output, x, y);
			x++;
		}
		x = 0;
		y++;
	}
	mlx_put_image_to_window(main->mlx, main->win, main->img, 0, 0);
	return (0);
}

int	main_pipeline(t_main *main)
{
	mlx_loop_hook(main->mlx, render, main);
	key_handles(main);
	mlx_loop(main->mlx);
	return (0);
}
