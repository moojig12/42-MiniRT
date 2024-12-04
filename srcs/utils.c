/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 08:05:16 by root              #+#    #+#             */
/*   Updated: 2024/12/04 08:05:42 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
