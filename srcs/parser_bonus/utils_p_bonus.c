/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_p_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:47:03 by fjoestin          #+#    #+#             */
/*   Updated: 2024/12/08 16:17:50 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

void	pop_material(t_emission *material, char **input)
{
	int	size;

	size = check_size_matrix(input);
	if (0 < size)
		material->reflect = ft_atof(input[0]);
	if (1 < size)
		material->diffuse = ft_atof(input[1]);
	if (2 < size)
		material->sampsize = ft_atof(input[2]);
}
