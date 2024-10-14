/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:07:11 by fjoestin          #+#    #+#             */
/*   Updated: 2024/10/14 22:07:12 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_camera	*parse_cam(t_world *world, char **input)
{
	t_camera	*ret;
	int			size;
	// if (index < 1 || index > 3)
	// 	printf("Error\nInvalid input for camera %i\n", index);
	ret = malloc(sizeof(t_camera));
	size = check_size_matrix(input);
	if (world->cam != NULL || size < 1 || size > 3)
		exit_err_init("Error\nToo many arg for cam\n", 1, world);
	if (input[1])
		pop_vec(&ret->pos ,ft_split(input, ','), NULL);
	else
		exit_err_init("Error\nInvalid input for camera\n", 1, world);
	if (input[2])
		pop_vec(&ret->norm, ft_split(input, ','), alloc_float(-1.0, 1.0));
	else
		exit_err_init("Error\nInvalid input for camera\n", 1, world);
	if (input[3])
		pop_fov(&ret->fov, input, alloc_int(0, 180));
	else
		exit_err_init("Error\nInvalid input for camera\n", 1, world);
	return (ret);
}