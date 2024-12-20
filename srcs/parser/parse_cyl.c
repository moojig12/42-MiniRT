/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cyl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:08:01 by fjoestin          #+#    #+#             */
/*   Updated: 2024/12/19 19:28:58 by fjoestin         ###   ########.fr       */
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
	if (size != 6)
		exit_err_init("Error\nToo many args for cylinder\n", 1, world);
	new = malloc(sizeof(t_cyl));
	if (!input[1] || pop_vec(&new->pos, ft_split(input[1], ','), NULL, 1))
		exit_err_init("Error\nWrong vec range for cylinder", 1, world);
	if (!input[2] || pop_vec(&new->norm, ft_split(input[2], ','), \
		alloc_float(-1.0, 1.0), 0))
		exit_err_init("Error\nWrong vec range for cylinder", 1, world);
	if (input[3] && input[4])
	{
		new->diameter = ft_atof(input[3]);
		new->height = ft_atof(input[4]);
	}
	else
		exit_err_init("Error\nNo arguments for cylinder", 1, world);
	if (!input[5] || pop_color(&new->color, ft_split(input[5], ',')))
		exit_err_init("Error\nWrong color range for cylinder", 1, world);
	new->next = NULL;
	ft_lstadd_back_cyl_mrt(&world->cyl, new);
	return (0);
}
