/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 08:05:16 by root              #+#    #+#             */
/*   Updated: 2024/12/09 08:02:02 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	material_init(t_material *material, int type)
{
	if (type == METAL)
	{
		material->diffuse = 0.23;
		material->reflect = 0.77;
		material->spec = 0.2;
	}
	else if (type == METAL_ROUGH)
	{
		material->diffuse = 0.44;
		material->reflect = 0.56;
		material->spec = 0.6;
	}
	else if (type == PLASTIC)
	{
		material->diffuse = 0.80;
		material->reflect = 0.13;
		material->spec = 0.1;
	}
	else if (type == MIRROR)
	{
		material->reflect = 1.0;
		material->diffuse = 0.0;
		material->spec = 0.0;
	}
	else
	{
		material->diffuse = 0.5;
		material->reflect = 0.5;
		material->spec = 0.0;
	}
}

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 12 && c <= 15))
		return (1);
	else
		return (0);
}

	// Don't need this!
int	*alloc_int(int a, int b)
{
	int	*result;

	result = malloc(2 * (sizeof(int)));
	if (!result)
		return (NULL);
	result[0] = a;
	result[1] = b;
	return (result);
}

double	*alloc_float(double a, double b)
{
	double	*result;

	result = malloc(2 * (sizeof(double)));
	if (!result)
		return (NULL);
	result[0] = a;
	result[1] = b;
	return (result);
}

// returns 1 if within range. 0 if outside of range
int	ft_range(int num, int min, int max)
{
	if (num >= min || num <= max)
		return (1);
	else
		return (0);
}

// returns 1 if within range. 0 if outside of range
int	ft_range_f(double num, double min, double max)
{
	if (num >= min || num <= max)
		return (1);
	else
		return (0);
}
