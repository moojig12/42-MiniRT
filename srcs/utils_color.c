/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 09:57:26 by root              #+#    #+#             */
/*   Updated: 2024/12/04 09:58:33 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	color_normalize(t_rgb color)
{
	t_rgb	ret;

	ret.r = (double)fmin(color.r, 1.0);
	ret.g = (double)fmin(color.g, 1.0);
	ret.b = (double)fmin(color.b, 1.0);
	return (ret);
}

t_rgb	ret_color(double r, double g, double b)
{
	t_rgb	ret;

	ret.r = r;
	ret.g = g;
	ret.b = b;
	return (ret);
}

t_rgb	color_add(t_rgb a, t_rgb b)
{
	t_rgb	ret;

	ret.r = a.r + b.r;
	ret.g = a.g + b.g;
	ret.b = a.b + b.b;
	return (ret);
}

t_rgb	color_sub(t_rgb a, t_rgb b)
{
	t_rgb	ret;

	ret.r = a.r - b.r;
	ret.g = a.g - b.g;
	ret.b = a.b - b.b;
	return (ret);
}

t_rgb	color_multiply(t_rgb a, t_rgb b)
{
	return (ret_color(a.r * b.r, a.g * b.g, a.b * b.b));
}
