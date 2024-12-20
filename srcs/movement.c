/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmandakh <nmandakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:00:02 by root              #+#    #+#             */
/*   Updated: 2024/12/20 14:43:27 by nmandakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	move(t_obj *obj, t_vec	movement, int movement_code)
{
	t_vec		moved_vec;
	t_selected	selected;

	selected = discern_object(obj);
	printf("selected: %i\n", selected.type);
	(void)movement_code;
	if (selected.type != CAMERA)
	{
		moved_vec = matrix_translation(*selected.pos, movement);
		*selected.pos = moved_vec;
	}
	else
	{
		moved_vec = matrix_translation(*selected.pos, movement);
		*selected.pos = moved_vec;
	}
	return (0);
}

int	rotate_object(t_obj *object, t_vec rotation)
{
	t_vec		rotated_vec;
	t_selected	selected;
	t_vec		right;

	selected = discern_object(object);
	if (selected.type != LIGHT && selected.type != SPHERE)
	{
		rotated_vec = matrix_rotation(*selected.norm, rotation);
		*selected.norm = rotated_vec;
		if (selected.type == CAMERA)
		{
			*selected.dir = matrix_rotation(*selected.dir, rotation);
			right = vec_normalize(\
			vec_cross(*selected.dir, *selected.norm));
			*selected.norm = vec_normalize(\
			vec_cross(right, *selected.dir));
		}
	}
	else
		printf("Can't rotate this object!\n");
	return (0);
}

void	emmit(t_obj *obj)
{
	if (obj->emissive == 1)
		obj->emissive = 0;
	else
		obj->emissive = 1;
}

int	movement(int key_code, t_main *main)
{
	printf("keycode: %i\n", key_code);
	if (!main->world->selected)
	{
		set_selection(main->world->selected, main, CAMERA);
		printf("Initiated\n");
	}
	check_selection(key_code, main);
	miscel_keys(key_code, main);
	if (key_code == ROTATE_LEFT)
		rotate_left(main);
	if (key_code == ROTATE_RIGHT)
		rotate_right(main);
	if (key_code == 103)
		emmit(main->world->selected);
	movement_selected(key_code, main->world->selected);
	rotation_selected(key_code, main->world->selected);
	return (1);
}
