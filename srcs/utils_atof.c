/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_atof.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:01:37 by root              #+#    #+#             */
/*   Updated: 2024/12/05 08:00:23 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	fract(double *fraction, int has_fraction, char str, double result)
{
	if (has_fraction)
	{
		*fraction *= 0.1;
		result += *fraction * (str - '0');
	}
	else
		result = result * 10.0 + (str - '0');
	return (result);
}

int	sign_fract(char **str, int sign)
{
	if (**str == '-')
	{
		sign = -1;
		(*str)++;
	}
	else
		sign = 1;
	return (sign);
}

// Function expects proper input! No '+' allowed
double	ft_atof(char *str)
{
	t_atof	f;

	f.result = 0.0;
	f.fraction = 1.0;
	f.has_fraction = 0;
	if (!str)
		return (0.0);
	f.sign = sign_fract(&str, f.sign);
	while (*str)
	{
		if (ft_isdigit(*str))
			f.result = fract(&f.fraction, f.has_fraction, *str, f.result);
		else if (*str == '.')
		{
			if (f.has_fraction)
				break ;
			f.has_fraction = 1;
		}
		else
			break ;
		str++;
	}
	return (f.result * f.sign);
}
