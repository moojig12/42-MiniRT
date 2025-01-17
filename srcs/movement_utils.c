/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 08:08:24 by root              #+#    #+#             */
/*   Updated: 2024/12/17 16:35:05 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	rotate_angle(int direction, double angle)
{
	if (direction == X_AXIS)
		return (vec(angle, 0, 0, 0));
	if (direction == Y_AXIS)
		return (vec(0, angle, 0, 0));
	if (direction == Z_AXIS)
		return (vec(0, 0, angle, 0));
	return (vec(0, 0, 0, 0));
}

t_vec	movement_rotation(t_vec movement, int movement_code)
{
	if (movement_code == FORWARD)
		return (vec(0, 0, 0, 0));
	if (movement_code == BACK)
		return (rotate_angle(Y_AXIS, 180));
	if (movement_code == LEFT)
		return (rotate_angle(Y_AXIS, -90));
	if (movement_code == RIGHT)
		return (rotate_angle(Y_AXIS, 90));
	if (movement_code == UP)
		return (rotate_angle(X_AXIS, -90));
	if (movement_code == DOWN)
		return (rotate_angle(X_AXIS, 90));
	return (movement);
}

t_vec	move_angle(int direction, double angle)
{
	if (direction == X_AXIS)
		return (vec(angle, 0, 0, 1));
	if (direction == Y_AXIS)
		return (vec(0, angle, 0, 1));
	if (direction == Z_AXIS)
		return (vec(0, 0, angle, 1));
	return (vec(0, 0, 0, 1));
}

void	print_position(t_obj *selection)
{
	t_selected	position;

	position = discern_object(selection);
	print_vec("Position:", *position.pos);
	if (position.norm)
		print_vec("Orientation:", *position.norm);
}

void	flush_screen(t_main *main, t_rgb **output)
{
	int	output_color;
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < main->world->cam->height)
	{
		while (x < main->world->cam->width)
		{
			output[y][x] = ret_color(0, 0, 0);
			output_color = pack_color(output[y][x]);
			mlx_pixel_put(main->mlx, main->win, x, y, output_color);
			x++;
		}
		y++;
	}
}
