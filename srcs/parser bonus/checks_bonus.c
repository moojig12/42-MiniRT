/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:54:20 by fjoestin          #+#    #+#             */
/*   Updated: 2024/12/04 07:07:59 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_file(char *file)
{
	while (*file != '\0' && *file != '.')
		file++;
	if (ft_strcmp(file, ".rt") == 0)
		return (0);
	else
		return (-1);
}

int	check_size_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return (-1);
	i = 0;
	while (matrix[i])
		i++;
	return (i);
}
