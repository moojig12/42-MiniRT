/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:54:20 by fjoestin          #+#    #+#             */
/*   Updated: 2024/10/14 19:30:13 by fjoestin         ###   ########.fr       */
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

	i = 0;
	if (!matrix)
		return (-1);
	while(matrix[i]){
		printf("line: %s\n", matrix[i]);
		i++;
	}
	return(i);
}