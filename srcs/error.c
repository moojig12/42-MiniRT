/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:17:00 by fjoestin          #+#    #+#             */
/*   Updated: 2024/10/14 17:40:39 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	exit_err_init(char *msg, int code, t_world *world)
{
	write(2, msg, ft_strlen(msg));
	if (world)
		free_world(world);
	exit (code);
}

void	exit_err(char *message, int code, t_main *main)
{
	write(2, message, ft_strlen(message));
	if(main)
		free_main(main);
	exit(code);
}

void	free_main(t_main *main)
{
	if (!main)
		return ;
	if (main->world)
		free_world(main->world);
	free(main);
}