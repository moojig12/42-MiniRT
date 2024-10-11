/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:17:00 by fjoestin          #+#    #+#             */
/*   Updated: 2024/10/07 16:21:37 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	exit_err(char *message, int code, t_main *main, t_world *world)
{
	write(2, message, ft_strlen(message));
	if(world)
		free_world(world);
	if(main)
		free_main(main);
	exit(code);
}

void	free_world(t_world *world)
{
	
}

void	free_main(t_main *main)
{

}