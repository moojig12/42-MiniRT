/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_gen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:25:03 by root              #+#    #+#             */
/*   Updated: 2024/12/08 15:30:43 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

unsigned int	ft_rand(void)
{
	static unsigned int	seed = 1;

	seed = A * seed + C;
	return (seed);
}

double	random_double(void)
{
	return (ft_rand() / (M + 1.0));
}

double	random_double_range(double min, double max)
{
	return (min + (max - min) * random_double());
}

t_vec	random_vec(double w)
{
	return (vec(random_double(), random_double(), random_double(), w));
}

t_vec	random_vec_range(double min, double max, double w)
{
	return (vec(random_double_range(min, max), \
			random_double_range(min, max), \
			random_double_range(min, max), w));
}
