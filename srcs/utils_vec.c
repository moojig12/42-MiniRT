/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmandakh <nmandakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:24:48 by root              #+#    #+#             */
/*   Updated: 2024/12/10 14:02:49 by nmandakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	vec(double x, double y, double z, double w)
{
	return ((t_vec){x, y, z, w});
}

t_vec	vec_add(t_vec a, t_vec b)
{
	return ((t_vec){a.x + b.x, a.y + b.y, a.z + b.z, a.w});
}

t_vec	vec_sub(t_vec a, t_vec b)
{
	return ((t_vec){a.x - b.x, a.y - b.y, a.z - b.z, a.w});
}

inline double	vec_dot(t_vec a, t_vec b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

t_vec	vec_multiply(t_vec a, t_vec b)
{
	t_vec	ret;

	ret.x = a.x * b.x;
	ret.y = a.y * b.y;
	ret.z = a.z * b.z;
	return (ret);
}
