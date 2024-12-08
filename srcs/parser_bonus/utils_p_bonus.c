/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_p_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:47:03 by fjoestin          #+#    #+#             */
/*   Updated: 2024/12/08 19:12:30 by fjoestin         ###   ########.fr       */
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

int	check_material(char *input)
{
	if (ft_strcmp(input, "metal") == 0)
		return (METAL);
	if (ft_strcmp(input, "glass") == 0)
		return (GLASS);
	if (ft_strcmp(input, "plastic") == 0)
		return (PLASTIC);
	return (STANDARD);
}

void	pop_material_basic(t_mat *material)
{
	material->reflect = 0.75;
	material->diffuse = 0.25;
}
