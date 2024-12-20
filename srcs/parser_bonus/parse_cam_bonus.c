/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmandakh <nmandakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:07:11 by fjoestin          #+#    #+#             */
/*   Updated: 2024/12/20 13:35:17 by nmandakh         ###   ########.fr       */
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
		exit_err_init("Error\nToo many arg for cam1\n", 1, world);
	if (!input[1] || pop_vec(&ret->pos, ft_split(input[1], ','), NULL, 1))
		exit_err_init("Error\nWrong vec range for cam2\n", 1, world);
	if (!input[2] || pop_vec(&ret->direction, ft_split(input[2], ','), \
		alloc_float(-1.0, 1.0), 0))
		exit_err_init("Error\nWrong vec range for cam3\n", 1, world);
	if (!input[3] || pop_fov(&ret->fov, input[3], alloc_int(0, 180)))
		exit_err_init("Error\nWrong fov range for cam\n", 1, world);
	return (ret);
}
