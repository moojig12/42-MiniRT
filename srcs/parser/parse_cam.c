/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:07:11 by fjoestin          #+#    #+#             */
/*   Updated: 2024/11/26 19:43:43 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_camera	*parse_cam(t_world *world, char **input)
{
	t_camera	*ret;
	int			size;
	ret = malloc(sizeof(t_camera));
	size = check_size_matrix(input);
	if (world->cam != NULL || size != 4)
		exit_err_init("Error\nToo many arg for cam\n", 1, world);
	if (input[1])
		pop_vec(&ret->pos ,ft_split(input[1], ','), NULL, 1);
	if (input[2])
		pop_vec(&ret->direction, ft_split(input[2], ','), alloc_float(-1.0, 1.0), 0);
	if (input[3])
		pop_fov(&ret->fov, input[3], alloc_int(0, 180));
	return (ret);
}