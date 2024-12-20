/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_color2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 09:57:45 by root              #+#    #+#             */
/*   Updated: 2024/12/17 16:35:47 by fjoestin         ###   ########.fr       */
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
	return (t << 24 | r << 16 | g << 8 | b);
}
