/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:17:00 by fjoestin          #+#    #+#             */
/*   Updated: 2024/12/04 10:24:53 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	exit_err_init(char *msg, int code, t_world *world)
{
	if (msg)
		perror(msg);
	if (world)
		free_world(world);
	exit (code);
}

void	exit_err(char *message, int code, t_main *main)
{
	if (message)
		perror(message);
	if (main)
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
