/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_atof.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:01:37 by root              #+#    #+#             */
/*   Updated: 2024/12/04 10:13:30 by root             ###   ########.fr       */
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

int	fraction_check(int *has_fraction, char c)
{
	if (c == '.')
	{
		if (*has_fraction == 1)
			return (1);
		*has_fraction = 1;
	}
	return (0);
}

// Function expects proper input! No '+' allowed
double	ft_atof(char *str)
{
	double	result;
	double	fraction;
	int		has_fraction;
	int		sign;

	result = 0.0;
	fraction = 1.0;
	has_fraction = 0;
	if (!str)
		return (0.0);
	sign = sign_fract(&str, sign);
	while (*str)
	{
		if (ft_isdigit(*str))
			result = fract(&fraction, has_fraction, *str, result);
		else if (!fraction_check(&has_fraction, *str))
			break ;
		else
			break ;
		str++;
	}
	return (result * sign);
}
