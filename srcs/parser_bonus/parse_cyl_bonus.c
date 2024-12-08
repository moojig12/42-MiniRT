/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cyl_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:08:01 by fjoestin          #+#    #+#             */
/*   Updated: 2024/12/08 18:56:02 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_lstadd_back_cyl_mrt(t_cyl **lst, t_cyl *new)
{
	t_cyl	*last;

	last = ft_lstlast_cyl_mrt(*lst);
	if (!last)
		*lst = new;
	else
	{
		last->next = new;
		new->next = NULL;
	}
}

t_cyl	*ft_lstlast_cyl_mrt(t_cyl *lst)
{
	t_cyl	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
	{
		temp = temp->next;
	}
	return (temp);
}

int	parse_cyl(t_world *world, char **input)
{
	t_cyl	*new;
	int		size;

	size = check_size_matrix(input);
	if (size < 6 || size > 7)
		exit_err_init("Error\nToo many args for cylinder\n", 1, world);
	new = malloc(sizeof(t_cyl));
	if (input[1])
		pop_vec(&new->pos, ft_split(input[1], ','), NULL, 1);
	if (input[2])
		pop_vec(&new->norm, ft_split(input[2], ','), alloc_float(-1.0, 1.0), 0);
	if (input[3])
		new->diameter = ft_atof(input[3]);
	if (input[4])
		new->height = ft_atof(input[4]);
	if (input[5])
		pop_color(&new->color, ft_split(input[5], ','));
	if (input[6])
		new->material = check_material(input[6]);
	new->next = NULL;
	ft_lstadd_back_cyl_mrt(&world->cyl, new);
	return (0);
}
