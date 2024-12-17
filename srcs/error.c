/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmandakh <nmandakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:17:00 by fjoestin          #+#    #+#             */
/*   Updated: 2024/12/17 13:52:17 by nmandakh         ###   ########.fr       */
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

void	free_buffer(t_rgb **output, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(output[i]);
		i++;
	}
	free(output);
}

void	free_main(t_main *main)
{
	if (!main)
		return ;
	if (main->world)
		free_world(main->world);
	if (main->output)
		free_buffer(main->output, main->height);
	if (main->img)
		mlx_destroy_image(main->mlx, main->img);
	mlx_clear_window(main->mlx, main->win);
	if (main->win)
		mlx_destroy_window(main->mlx, main->win);
	if (main->mlx)
		mlx_destroy_display(main->mlx);
	free(main);
}
