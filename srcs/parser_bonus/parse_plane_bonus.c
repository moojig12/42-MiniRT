/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:08:18 by fjoestin          #+#    #+#             */
/*   Updated: 2024/12/20 13:19:00 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_lstadd_back_plane_mrt(t_plane **lst, t_plane *new)
{
	t_plane	*last;

	last = ft_lstlast_plane_mrt(*lst);
	if (!last)
		*lst = new;
	else
	{
		last->next = new;
		new->next = NULL;
	}
}

t_plane	*ft_lstlast_plane_mrt(t_plane *lst)
{
	t_plane	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

int	parse_plane(t_world *world, char **input)
{
	t_plane	*new;
	int		size;

	new = malloc(sizeof(t_plane));
	size = check_size_matrix(input);
	if (size < 4 || size > 5)
		exit_err_init("Error\nToo many args for plane\n", 1, world);
	if (!input[1] || pop_vec(&new->pos, ft_split(input[1], ','), NULL, 1))
		exit_err_init("Error\nWrong vec range for plane\n", 1, world);
	if (!input[2] || pop_vec(&new->norm, ft_split(input[2], ','), \
		alloc_float(-1.0, 1.0), 0))
		exit_err_init("Error\nWrong vec range for plane\n", 1, world);
	if (!input[3] || pop_color(&new->color, ft_split(input[3], ',')))
		exit_err_init("Error\nWrong color range for plane\n", 1, world);
	material_init(&new->material, check_material(input[4]));
	new->next = NULL;
	ft_lstadd_back_plane_mrt(&world->plane, new);
	return (0);
}
