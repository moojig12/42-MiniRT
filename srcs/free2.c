/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmandakh <nmandakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 09:55:18 by root              #+#    #+#             */
/*   Updated: 2024/12/10 15:03:14 by nmandakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_plane(t_plane *plane)
{
	t_plane	*next;

	if (!plane)
		return ;
	while (plane)
	{
		next = plane->next;
		free(plane);
		plane = next;
	}
}

void	free_cyl(t_cyl *cyl)
{
	t_cyl	*next;

	if (!cyl)
		return ;
	while (cyl)
	{
		next = cyl->next;
		free(cyl);
		cyl = next;
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
