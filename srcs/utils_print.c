/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:01:23 by root              #+#    #+#             */
/*   Updated: 2024/12/17 16:35:55 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* double	trace_time(int type)
{
	static clock_t	last_time = 0;
	clock_t			current_time;
	double elapsed_time;

	current_time = clock();
	elapsed_time = 0.0;
	if (last_time != 0)
		elapsed_time = (double)(current_time - last_time) / CLOCKS_PER_SEC;
	last_time = current_time;

	if (type == 1)
		return (elapsed_time);
	else
		printf("Time elapsed: %f\n\n", elapsed_time);

	return (elapsed_time);
} */

int	print_color(char *string, t_rgb color)
{
	if (string)
		printf("\n---\n%s\nr: %f\ng: %f\nb: %f\n", \
		string, color.r, color.g, color.b);
	else
		printf("---\nr: %f\ng: %f\nb: %f\n", \
		color.r, color.g, color.b);
	return (0);
}

int	print_matrix(char *string, t_matrix mat)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("%s\n", string);
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			printf("%f ", mat.matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	return (0);
}

int	print_vec(char *string, t_vec vec)
{
	if (string)
		printf("\n---\n%s\nx: %f\ny: %f\nz: %f\nw: %f\n", \
		string, vec.x, vec.y, vec.z, vec.w);
	else
		printf("---\nx: %f\ny: %f\nz: %f\nw: %f\n", \
		vec.x, vec.y, vec.z, vec.w);
	return (0);
}
