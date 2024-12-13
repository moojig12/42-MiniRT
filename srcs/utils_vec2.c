/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vec2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 08:05:54 by root              #+#    #+#             */
/*   Updated: 2024/12/11 23:38:19 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	vec_cross(t_vec a, t_vec b)
{
	t_vec	ret;

	ret.x = a.y * b.z - a.z * b.y;
	ret.y = a.z * b.x - a.x * b.z;
	ret.z = a.x * b.y - a.y * b.x;
	return (ret);
}

double	vec_length(t_vec v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec	vec_scalar(t_vec a, double b)
{
	t_vec	ret;

	ret.x = a.x * b;
	ret.y = a.y * b;
	ret.z = a.z * b;
	return (ret);
}

t_vec	vec_normalize(t_vec v)
{
	double	magnitude;
	double inv_mag;

	magnitude = v.x * v.x + v.y * v.y + v.z * v.z;
	if (magnitude < 1e-6)
		return ((t_vec){0, 0, 0, 0});
	inv_mag = 1.0 / sqrt(magnitude);
	return ((t_vec){v.x * inv_mag, v.y * inv_mag, v.z * inv_mag, 1});
}
