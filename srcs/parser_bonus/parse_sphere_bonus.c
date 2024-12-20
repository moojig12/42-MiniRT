/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:08:34 by fjoestin          #+#    #+#             */
/*   Updated: 2024/12/20 13:19:55 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_lstadd_back_sphere_mrt(t_sphere **lst, t_sphere *new)
{
	t_sphere	*last;

	last = ft_lstlast_sphere_mrt(*lst);
	if (!last)
		*lst = new;
	else
	{
		last->next = new;
		new->next = NULL;
	}
}

t_sphere	*ft_lstlast_sphere_mrt(t_sphere *lst)
{
	t_sphere	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
	{
		temp = temp->next;
	}
	return (temp);
}

int	parse_sphere(t_world *world, char **input)
{
	int			size;
	t_sphere	*new;

	size = check_size_matrix(input);
	if (size < 4 || size > 5)
		exit_err_init("Error\nToo many args for sphere\n", 1, world);
	new = malloc(sizeof(t_sphere));
	if (input[1])
		pop_vec(&new->pos, ft_split(input[1], ','), NULL, 1);
	if (input[2])
		new->diameter = ft_atof(input[2]);
	if (input[3])
		pop_color(&new->color, ft_split(input[3], ','));
	material_init(&new->material, check_material(input[4]));
	new->next = NULL;
	ft_lstadd_back_sphere_mrt(&world->sphere, new);
	return (0);
}
