/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_ops2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 08:16:52 by root              #+#    #+#             */
/*   Updated: 2024/12/04 08:18:35 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	rotate_x(t_matrix mat, double angle)
{
	t_matrix	post;

	(void)mat;
	post = identity_matrix();
	angle = angle * (PI / 180);
	post.matrix[1][1] = cos(angle);
	post.matrix[1][2] = -sin(angle);
	post.matrix[2][1] = sin(angle);
	post.matrix[2][2] = cos(angle);
	return (post);
}

t_matrix	rotate_y(t_matrix mat, double angle)
{
	t_matrix	post;

	(void)mat;
	post = identity_matrix();
	angle = angle * (PI / 180);
	post.matrix[0][0] = cos(angle);
	post.matrix[2][0] = -sin(angle);
	post.matrix[0][2] = sin(angle);
	post.matrix[2][2] = cos(angle);
	return (post);
}

t_matrix	rotate_z(t_matrix mat, double angle)
{
	t_matrix	post;

	(void)mat;
	post = identity_matrix();
	angle = angle * (PI / 180);
	post.matrix[0][0] = cos(angle);
	post.matrix[0][1] = -sin(angle);
	post.matrix[1][0] = sin(angle);
	post.matrix[1][1] = cos(angle);
	return (post);
}

t_matrix	empty_matrix(void)
{
	t_matrix	post;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (i < 4)
	{
		while (j < 4)
		{
			post.matrix[i][j] = 0;
			j++;
		}
		j = 0;
		i++;
	}
	return (post);
}

t_matrix	identity_matrix(void)
{
	t_matrix	post;
	int			i;

	post = empty_matrix();
	i = 0;
	while (i < 4)
	{
		post.matrix[i][i] = 1;
		i++;
	}
	return (post);
}
