/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_amb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:08:48 by fjoestin          #+#    #+#             */
/*   Updated: 2024/10/17 15:04:45 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ambient	*parse_amb(t_world *world, char **input)
{
	double		*range;
	t_ambient	*new;
	int			size;

	range = alloc_float(0.0, 1.0);
	new = malloc(sizeof(t_ambient));
	size = check_size_matrix(input);
	if (world->amb != NULL || size != 3)
		exit_err_init("Error\nToo many args for amb\n", 1, world);
	if (input[1] && ft_range_f(ft_atof(input[1]), range[0], range[1]))
		new->ratio = ft_atof(input[1]);
	else
		exit_err_init("Error\nWrong ambience light ratio\n", 1, world);
	if (input[2])
		pop_color(&new->color, ft_split(input[2], ','));
	else
		exit_err_init("Error\ninvalid input for ambience\n", 1, world);
	return (new);
}