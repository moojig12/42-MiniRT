#include "../minirt.h"

int	move(t_obj *obj, t_vec	movement, int movement_code)
{
	t_vec		movement_angle;
	t_vec		moved_vec;
	t_selected	selected;

	selected = discern_object(obj);

	if (selected.type != CAMERA)
	{
		moved_vec = matrix_translation(*selected.pos, movement);
		*selected.pos = moved_vec;
	}
	else
	{
		movement_angle = movement_rotation(movement, movement_code);
		moved_vec = matrix_rotation(*selected.dir, movement_angle);
		moved_vec = vec_normalize(moved_vec);
		*selected.pos = vec_add(*selected.pos, moved_vec);
		return (0);
	}

	return (0);
}

int	rotate_left(t_main *main)
{
	t_vec	rotated_vec;

	rotated_vec = matrix_rotation(main->world->cam->direction, vec(0, -15, 0, 0));
	main->world->cam->direction = rotated_vec;

	return (0);
}

int	rotate_right(t_main *main)
{
	t_vec	rotated_vec;

	rotated_vec = matrix_rotation(main->world->cam->direction, vec(0, 15, 0, 0));
	main->world->cam->direction = rotated_vec;

	return (0);
}

int	rotate_object(t_obj *object, t_vec rotation)
{
	t_vec	rotated_vec;
	t_selected	selected;

	selected = discern_object(object);
	if (selected.type != LIGHT && selected.type != SPHERE)
	{
		rotated_vec = matrix_rotation(*selected.norm, rotation);
		*selected.norm = rotated_vec;
		if (selected.type == CAMERA)
		{
			*selected.dir = matrix_rotation(*selected.dir, rotation);
			t_vec	right = vec_normalize(vec_cross(*selected.dir, *selected.norm));
			*selected.norm = vec_normalize(vec_cross(right, *selected.dir));
		}
	}
	else
		printf("Can't rotate this object!\n");
	return (0);
}

int	movement(int key_code, t_main *main)
{
	//int		type;

	printf("keycode: %i\n", key_code);
	if (!main->world->selected)
	{
		main->world->selected = malloc(sizeof(t_obj *));
		set_selection(main->world->selected, main, CAMERA);
		printf("mallocated\n");
	}
	//type = (*main->world->selected)->type;
	check_selection(key_code, main);
	if (key_code == KEY_R)
	{
		if (main->render_switch == HIGH)
		{
			main->render_switch = LOW;
			printf("Render mode is now set to: LOW\n");
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
	if (key_code == ROTATE_LEFT)
		rotate_left(main);
	if (key_code == ROTATE_RIGHT)
		rotate_right(main);
	if (key_code == KEY_P)
		print_position((t_obj *)(*main->world->selected));

	movement_selected(key_code, (t_obj *)*(main->world->selected));
	rotation_selected(key_code, (t_obj *)(*main->world->selected));
	return (1);
}