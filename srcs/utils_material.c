/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:04:30 by root              #+#    #+#             */
/*   Updated: 2024/12/17 16:35:51 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	material_pop(t_material *material, double roughness, \
double metalness, double specular)
{
	material->metalness = metalness;
	material->roughness = roughness;
	material->spec = specular;
}

void	material_init(t_material *material, int type)
{
	if (type == METAL)
		material_pop(material, 0.13, 0.77, 0.94);
	else if (type == METAL_ROUGH)
		material_pop(material, 0.44, 0.56, 0.78);
	else if (type == PLASTIC)
		material_pop(material, 0.8, 0.13, 0.56);
	else if (type == MIRROR)
		material_pop(material, 0.1, 1.0, 1.0);
	else if (type == ROCK)
		material_pop(material, 1.0, 0.0, 0.1);
	else
		material_pop(material, 1, 0.5, 0.5);
}
