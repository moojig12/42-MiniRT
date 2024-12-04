/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_misc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 08:09:06 by root              #+#    #+#             */
/*   Updated: 2024/12/04 08:09:30 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	miscel_keys(int key_code, t_main *main)
{
	if (key_code == KEY_R)
	{
		if (main->render_switch == HIGH)
		{
			printf("Render mode is now set to: LOW\n");
			main->render_switch = LOW;
		}
		else
		{
			printf("Render mode is now set to: HIGH\n");
			main->render_switch = HIGH;
		}
		flush_screen(main, main->output);
	}
	if (key_code == ESC_WIN)
		close_window(main);
	if (key_code == KEY_P)
		print_position(main->world->selected);
}

int	rotate_left(t_main *main)
{
	t_vec	rotated_vec;

	rotated_vec = matrix_rotation(main->world->cam->direction, \
	vec(0, -15, 0, 0));
	main->world->cam->direction = rotated_vec;
	return (0);
}

int	rotate_right(t_main *main)
{
	t_vec	rotated_vec;

	rotated_vec = matrix_rotation(main->world->cam->direction, \
	vec(0, 15, 0, 0));
	main->world->cam->direction = rotated_vec;
	return (0);
}
