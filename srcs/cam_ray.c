/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 08:04:56 by root              #+#    #+#             */
/*   Updated: 2024/12/04 08:04:56 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	gen_ray(t_camera *cam, int x, int y)
{
	t_ray		ray;
	t_screen	screen;

	screen.aspect_ratio = ((double)cam->width / (double)cam->height);
	screen.ndc_x = (x + 0.5) / cam->width;
	screen.ndc_y = (y + 0.5) / cam->height;
	screen.pixel_x = (2 * screen.ndc_x - 1) * \
	tan((double)cam->fov * 0.5 * PI / 180) * screen.aspect_ratio;
	screen.pixel_y = (1 - 2 * screen.ndc_y) * \
	tan((double)cam->fov * 0.5 * PI / 180);
	screen.forward = vec_normalize(cam->direction);
	screen.right = vec_normalize(vec_cross(cam->norm, screen.forward));
	screen.up = vec_cross(screen.forward, screen.right);
	ray.origin = cam->pos;
	ray.dest = vec_add(vec_add(vec_scalar(screen.right, screen.pixel_x), \
		vec_scalar(screen.up, screen.pixel_y)), vec_scalar(screen.forward, 1));
	ray.dest = vec_normalize(ray.dest);
	return (ray);
}

t_ray	gen_ray_low(t_camera *cam, int x, int y)
{
	t_ray		ray;
	t_screen	screen;

	screen.aspect_ratio = ((double)cam->width / (double)cam->height);
	screen.ndc_x = (x + 0.5) / cam->width;
	screen.ndc_y = (y + 0.5) / cam->height;
	screen.pixel_x = (2 * screen.ndc_x - 1) * \
	tan((double)cam->fov * 0.5 * PI / 180) * screen.aspect_ratio;
	screen.pixel_y = (1 - 2 * screen.ndc_y) * \
	tan((double)cam->fov * 0.5 * PI / 180);
	screen.forward = vec_normalize(cam->direction);
	screen.right = vec_normalize(vec_cross(cam->norm, screen.forward));
	screen.up = vec_cross(screen.forward, screen.right);
	ray.origin = cam->pos;
	ray.dest = vec_add(vec_add(vec_scalar(screen.right, screen.pixel_x), \
		vec_scalar(screen.up, screen.pixel_y)), vec_scalar(screen.forward, 1));
	ray.dest = vec_normalize(ray.dest);
	return (ray);
}
