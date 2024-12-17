/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 08:17:44 by root              #+#    #+#             */
/*   Updated: 2024/12/17 16:34:54 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	matrix_multiply(t_matrix a, t_matrix b)
{
	t_matrix	post;
	int			i;
	int			j;
	int			k;

	post = empty_matrix();
	i = 0;
	j = 0;
	k = 0;
	while (i < 4)
	{
		while (j < 4)
		{
			while (k < 4)
			{
				post.matrix[i][j] = a.matrix[i][k] * b.matrix[k][j];
				k++;
			}
			k = 0;
			j++;
		}
		j = 0;
		i++;
	}
	return (post);
}

t_vec	matrix_dot(t_matrix mat, t_vec vec)
{
	t_vec		post;
	double		temp[4];
	int			i;

	i = 0;
	while (i < 4)
	{
		temp[i] = mat.matrix[i][0] * vec.x \
				+ mat.matrix[i][1] * vec.y \
				+ mat.matrix[i][2] * vec.z \
				+ mat.matrix[i][3] * vec.w;
		i++;
	}
	post.x = temp[0];
	post.y = temp[1];
	post.z = temp[2];
	post.w = temp[3];
	return (post);
}

t_vec	matrix_translation(t_vec data, t_vec translate)
{
	t_matrix	post;
	t_vec		ret;

	post = identity_matrix();
	post.matrix[0][3] = translate.x;
	post.matrix[1][3] = translate.y;
	post.matrix[2][3] = translate.z;
	post.matrix[3][3] = translate.w;
	ret = matrix_dot(post, data);
	return (ret);
}

t_vec	matrix_rotation(t_vec data, t_vec rotate)
{
	t_matrix	post;
	t_matrix	x_rotation;
	t_matrix	y_rotation;
	t_matrix	z_rotation;
	t_vec		result;

	post = identity_matrix();
	x_rotation = rotate_x(post, rotate.x);
	y_rotation = rotate_y(post, rotate.y);
	z_rotation = rotate_z(post, rotate.z);
	result = matrix_dot(x_rotation, data);
	result = matrix_dot(y_rotation, result);
	result = matrix_dot(z_rotation, result);
	return (result);
}
