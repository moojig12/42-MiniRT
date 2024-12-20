/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmandakh <nmandakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 19:21:15 by root              #+#    #+#             */
/*   Updated: 2024/12/20 14:46:37 by nmandakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_color_to_buff(t_main *main, t_rgb **output, int x, int y)
{
	int	output_color;

	output_color = pack_color(output[y][x]);
	if (main->render_switch == LOW)
		output[y][x] = ret_color(0, 0, 0);
	put_pixel_to_img(output_color, *main, x, y);
}

t_vec	cone_pewpew(t_vec norm, t_material *mat, t_ray ray)
{
	t_vec	ret;
	t_vec	diffuse_dir;
	t_vec	reflected;
	t_vec	spread_dir;

	ray.dest = vec_normalize(ray.dest);
	norm = vec_normalize(norm);
	if (mat->metalness == 1)
		return (vec_sub(ray.dest, vec_scalar(norm, 2.0 * \
		vec_dot(ray.dest, norm))));
	diffuse_dir = random_vec_range(-1.0, 1.0, 0);
	if (vec_dot(diffuse_dir, norm) < 0)
		diffuse_dir = vec_scalar(diffuse_dir, -1);
	reflected = vec_sub(ray.dest, \
	vec_scalar(norm, 2.0 * vec_dot(ray.dest, norm)));
	spread_dir = vec_add(vec_scalar(reflected, 1.0 - mat->roughness), \
		vec_scalar(diffuse_dir, mat->roughness));
	spread_dir = vec_normalize(spread_dir);
	ret = spread_dir;
	return (vec_normalize(ret));
}

	// Hybrid brdf, with Fresnel and Cook-torrance
double	brdf_calculation(t_material mat, t_ray ray, t_vec norm)
{
	double	fresnel;
	double	diffuse;
	double	cos_theta;

	cos_theta = vec_dot(ray.dest, norm);
	fresnel = mat.metalness + (1 - mat.metalness) * pow(1.0 - cos_theta, 5.0);
	diffuse = (mat.roughness) * cos_theta;
	return (diffuse + fresnel);
}

// Checking for direct occlusion to a single point light
t_rgb	direct_light_occlusion(t_intersect intersect, t_world *world, \
t_rgb return_color)
{
	t_ray	shadow_ray;
	t_rgb	light_contribution;
	double	attenuation;
	double	light_distance;
	double	cos_theta;

	shadow_ray.origin = vec_add(intersect.point, vec_scalar(intersect.norm, \
	EPSILON));
	shadow_ray.dest = vec_normalize(vec_sub(world->light->pos, \
	shadow_ray.origin));
	light_distance = vec_length(vec_sub(world->light->pos, intersect.point));
	if (!is_occluded(shadow_ray, world, light_distance))
	{
		attenuation = 1.0 / (light_distance * light_distance);
		cos_theta = vec_dot(intersect.norm, shadow_ray.dest);
		cos_theta = fmax(0.0, cos_theta);
		light_contribution = color_scalar(color_multiply(world->light->color, \
				intersect.color), cos_theta * attenuation * \
				world->light->brightness * \
				brdf_calculation(intersect.material, shadow_ray, \
				intersect.norm));
		return_color = color_add(return_color, light_contribution);
	}
	return (color_normalize(return_color));
}

void	put_pixel_to_img(int color, t_main main, int x, int y)
{
	char	*pxl;

	if (x >= 0 && x < main.width && y >= 0 && y < main.height)
	{
		pxl = main.addr + (y * main.line_length + x *(main.bits_per_pixel / 8));
		*(unsigned int *)pxl = color;
	}
}
