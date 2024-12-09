/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_p_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:47:03 by fjoestin          #+#    #+#             */
/*   Updated: 2024/12/09 08:19:26 by root             ###   ########.fr       */
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

void	pop_material_basic(t_material *material)
{
	material->diffuse = 0.80;
	material->reflect = 0.13;
}
