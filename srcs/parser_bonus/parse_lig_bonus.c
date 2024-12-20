/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lig_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:07:43 by fjoestin          #+#    #+#             */
/*   Updated: 2024/12/20 13:14:47 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	*parse_light(t_world *world, char **input)
{
	t_light	*new;
	int		size;

	size = check_size_matrix(input);
	if (world->light != NULL || size != 4)
		exit_err_init("Error\nToo many args for light\n", 1, world);
	new = malloc(sizeof(t_light));
	if (!input[1] || pop_vec(&new->pos, ft_split(input[1], ','), NULL, 1))
		exit_err_init("Error\nWrong vec range for light\n", 1, world);
	if (input[2] && ft_range(ft_atof(input[2]), 0.0, 1.0))
		new->brightness = ft_atof(input[2]);
	else
		exit_err_init("Error\nInvalid input for light\n", 1, world);
	if (!input[3] || pop_color(&new->color, ft_split(input[3], ',')))
		exit_err_init("Error\nWrong color range for light\n", 1, world);
	return (new);
}
