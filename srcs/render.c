/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:30:24 by fjoestin          #+#    #+#             */
/*   Updated: 2024/12/09 15:00:13 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	key_handles(t_main *main)
{
	mlx_key_hook(main->win, movement, main);
	mlx_hook(main->win, 17, 1L << 17, close_window, main);
}

	// The function for simulating and bouncing a ray off an object
t_rgb	trace_path(t_world *world, t_ray ray, int depth)
{
	t_intersect		intersection;
	t_rgb			return_color;
	t_rgb			incoming;
	t_ray			new_ray;
	double			brdf;

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
	return_color = color_multiply(world->amb->color, intersection.color);
	return_color = color_scalar(return_color, world->amb->ratio);
	return_color = direct_light_occlusion(intersection, world, return_color);
	return_color = color_add(return_color, color_scalar(incoming, brdf));
	return (color_normalize(return_color));
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
	while (y < main->height)
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