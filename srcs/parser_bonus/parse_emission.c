/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_emission.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:57:39 by fjoestin          #+#    #+#             */
/*   Updated: 2024/12/08 19:02:42 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_emission	*parse_emission(t_world *world, char **input)
{
	t_emission	*new;
	int			size;

	new = malloc(sizeof(t_emission));
	size = check_size_matrix(input);
	if (world->emission != NULL || size != 3)
		exit_err_init("Error\nToo many args for emission\n", 1, world);
	if (input[1])
		new->sampsize = ft_atoi(input[1]);
	if (input[2])
		new->depth = ft_atoi(input[2]);
	return (new);
}
