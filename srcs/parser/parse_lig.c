/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lig.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:07:43 by fjoestin          #+#    #+#             */
/*   Updated: 2024/10/14 22:20:56 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_lstadd_back_lig_mrt(t_light **lst, t_light *new)
{
	t_light	*last;

	last = ft_lstlast_lig_mrt(*lst);
	if (!last)
		*lst = new;
	else
	{
		last->next = new;
		new->next = NULL;
	}
}

t_light	*ft_lstlast_lig_mrt(t_light *lst)
{
	t_light	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}


int	parse_light(t_world *world, t_light *light, char **input)
{
	t_light	*new;
	int		size;

	size = check_size_matrix(input);
	if (size > 4 || size < 2)
		exit_err_init("Error\nToo many args for light\n", 1, world);
	new = malloc(sizeof(t_light));
	if (input[1])
		pop_vec(&new->pos, ft_split(input[1], ','), NULL);
	if (input[2] && ft_range(ft_atof(input[2]), 0.0, 1.0))
		new->brightness = ft_atof(input[2]);
	else
		exit_err_init("Error\nInvalid input for light\n", 1, world);
	if (input[3])
		pop_color(&new->color, ft_split(input[3], ','));
	new->next = NULL;
	ft_lstadd_back_lig_mrt(&light, new);
	return (0);
}