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
	printf("size of cam: %i\n", size);
	if (world->cam != NULL || size < 2 || size > 4)
		exit_err_init("Error\nToo many arg for cam\n", 1, world);
	if (input[1])
		pop_vec(&ret->pos ,ft_split(input[1], ','), NULL);
	if (input[2])
		pop_vec(&ret->norm, ft_split(input[2], ','), alloc_float(-1.0, 1.0));
	if (input[3])
		pop_fov(&ret->fov, input[3], alloc_int(0, 180));
	return (ret);
}