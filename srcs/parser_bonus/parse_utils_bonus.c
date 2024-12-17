/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 08:05:08 by root              #+#    #+#             */
/*   Updated: 2024/12/17 16:34:00 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_colors(t_rgb *rgb, char **input)
{
	rgb->r = (double)ft_atoi(input[0]) / 255;
	rgb->g = (double)ft_atoi(input[1]) / 255;
	rgb->b = (double)ft_atoi(input[2]) / 255;
}

int	pop_color(t_rgb *rgb, char **input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_range(ft_atof(input[i]), 0, 255))
		{
			printf("Error\nInvalid range for color");
			exit (0);
		}
		i++;
	}
	if (i != 3)
		return (1);
	else
		put_colors(rgb, input);
	i = 0;
	while (input[i])
	{
		free(input[i]);
		i++;
	}
	free(input);
	return (0);
}

void	free_double_array(char **input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		free(input[i]);
		i++;
	}
	free(input);
}

int	pop_vec(t_vec *pos, char **input, double *range, double type)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (range && !ft_range_f(ft_atof(input[i]), range[0], range[1]))
		{
			printf("Error\nInvalid range for vec\n");
			exit(0);
		}
		i++;
	}
	if (i != 3)
		return (1);
	else
		*pos = vec(ft_atof(input[0]), \
		ft_atof(input[1]), ft_atof(input[2]), type);
	i = 0;
	free_double_array(input);
	free(range);
	return (0);
}

int	pop_fov(int *fov, char *input, int *range)
{
	if (!input)
		return (0);
	if (ft_range(ft_atoi(input), range[0], range[1]))
		*fov = ft_atoi(input);
	free(range);
	return (0);
}
