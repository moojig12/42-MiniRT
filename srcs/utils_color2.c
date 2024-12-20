/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_color2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmandakh <nmandakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 09:57:45 by root              #+#    #+#             */
/*   Updated: 2024/12/20 13:49:11 by nmandakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	color_scalar(t_rgb a, double scalar)
{
	t_rgb	ret;

	ret.r = a.r * scalar;
	ret.g = a.g * scalar;
	ret.b = a.b * scalar;
	return (ret);
}

t_rgb	color_scalar_div(t_rgb a, double scalar)
{
	t_rgb	ret;

	ret.r = a.r / scalar;
	ret.g = a.g / scalar;
	ret.b = a.b / scalar;
	return (ret);
}

int	pack_color(t_rgb color)
{
	int	r;
	int	g;
	int	b;
	int	t;

	r = (int)(255.0 * color.r);
	g = (int)(255.0 * color.g);
	b = (int)(255.0 * color.b);
	t = 255;
	return ((unsigned)t << 24 | r << 16 | g << 8 | b);
}
