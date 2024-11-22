#include "minirt.h"

double	get_angle(t_vec	movement, t_vec norm)
{
	double	cos_theta;

	cos_theta = vec_dot(movement, norm);
	return (acos(cos_theta));
}

int	move(t_obj *obj, t_vec	movement)
{
	t_vec	moved_vec;
	t_selected	selected;

	selected = discern_object(obj);

	if (selected.type != CAMERA)
	{
		moved_vec = matrix_translation(*selected.pos, movement);
		*selected.pos = moved_vec;
	}
	else
	{
			// 1. Calculate the angle between the movement vector and the camera's normal
		double angle = get_angle(movement, *selected.norm);

		// 2. Determine the axis of rotation (cross product of movement and normal)
		t_vec rotation_axis = vec_cross(movement, *selected.norm);
		
		// 3. Combine the axis and angle into a single vector (angle_vec)
		t_vec angle_vec = vec_scalar(vec_normalize(rotation_axis), angle);
		 // 4. Rotate the movement vector to align with the camera's orientation
		t_vec aligned_movement = matrix_rotation(movement, angle_vec);

		// 5. Translate the rotated vector in 3D space to update the object's position
		t_vec updated_position = matrix_translation(*selected.pos, aligned_movement);

		// moved_vec = matrix_rotation(movement, angle_vec);
		// moved_vec = matrix_translation(*selected.pos, movement);
		*selected.pos = updated_position;
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

t_vec	rotate_angle(int direction, double angle)
{
	t_vec	rotation;

	if (direction == X_AXIS)
		return (vec(angle, 0, 0, 0));
	if (direction == Y_AXIS)
		return (vec(0, angle, 0, 0));
	if (direction == Z_AXIS)
		return (vec(0, 0, angle, 0));
	return (rotation);
}

t_vec	move_angle(int direction, double angle)
{
	t_vec	movement;

	if (direction == X_AXIS)
		return (vec(angle, 0, 0, 1));
	if (direction == Y_AXIS)
		return (vec(0, angle, 0, 1));
	if (direction == Z_AXIS)
		return (vec(0, 0, angle, 1));
	return (movement);
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

int	rotation_selected(int key_code, t_obj *selected)
{
	if (key_code == KEY_I)
		rotate_object(selected, rotate_angle(X_AXIS, -15));
	if (key_code == KEY_J)
		rotate_object(selected, rotate_angle(Y_AXIS, -15));
	if (key_code == KEY_K)
		rotate_object(selected, rotate_angle(X_AXIS, 15));
	if (key_code == KEY_L)
		rotate_object(selected, rotate_angle(Y_AXIS, 15));
	if (key_code == KEY_U)
		rotate_object(selected, rotate_angle(Z_AXIS, 15));
	if (key_code == KEY_O)
		rotate_object(selected, rotate_angle(Z_AXIS, -15));
}

int	movement_selected(int key_code, t_obj *selected)
{
	if (key_code == FORWARD)
		move(selected, move_angle(Z_AXIS, 1));
	if (key_code == LEFT)
		move(selected, move_angle(X_AXIS, -1));
	if (key_code == BACK)
		move(selected, move_angle(Z_AXIS, -1));
	if (key_code == RIGHT)
		move(selected, move_angle(X_AXIS, 1));
	if (key_code == UP)
		move(selected, move_angle(Y_AXIS, 1));
	if (key_code == DOWN)
		move(selected, move_angle(Y_AXIS, -1));
}

void	set_selection(t_obj **base_selection, t_main *main, int target)
{
	*base_selection = main->world->objlist;
	while (base_selection && (*base_selection)->type != target)
	{
		printf("object checked: %i\n", (*base_selection)->type);
		if ((*base_selection)->type == target)
			printf("FOUND!\n");
		(*base_selection) = (*base_selection)->next;
	}
	main->world->selected = base_selection;
	printf("selection set to %i\n", (*main->world->selected)->type);
}

void	set_position(t_obj *selection)
{
	t_selected	position;

	position = discern_object(selection);
	print_vec("Position:", *position.pos);
}

int	movement(int key_code, t_main *main)
{
	t_obj	**base_selection;
	int		type;

	printf("keycode: %i\n", key_code);
	if (!main->world->selected)
	{
		base_selection = malloc(sizeof(t_obj *));
		set_selection(base_selection, main, CAMERA);
		printf("mallocated\n");
	}
	else
	{
		type = (*main->world->selected)->type;
		if (key_code == OBJ_CAM)
		{
			if (type == CAMERA)
				printf("Camera already selected\n");
			else
				set_selection(main->world->selected, main, CAMERA);
		}
		else if (key_code == OBJ_LIGHT)
		{
			if (type == LIGHT)
				printf("Light already selected\n");
			else
				set_selection(main->world->selected, main, LIGHT);
		}
		else if (key_code == OBJ_CYL)
		{
			if (type == CYLINDER)
				printf("Cylinder already selected\n");
			else
				set_selection(main->world->selected, main, CYLINDER);
		}
		else if (key_code == OBJ_SPHERE)
		{
			if (type == SPHERE)
				printf("Sphere already selected\n");
			else
				set_selection(main->world->selected, main, SPHERE);
		}
		else if (key_code == OBJ_PLANE)
		{
			if (type == PLANE)
				printf("Plane already selected\n");
			else
				set_selection(main->world->selected, main, PLANE);
		}
	}
	// printf("keycode: %i\n", key_code);
	if (key_code == ESC_WIN)
		close_window(main);
	if (key_code == ROTATE_LEFT)
		rotate_left(main);
	if (key_code == ROTATE_RIGHT)
		rotate_right(main);
	if (key_code == 112)
		set_position((t_obj *)(*main->world->selected));
	
	// print_vec("test:", ((t_camera *)((t_obj *)(*main->world->selected)->data))->direction);
	movement_selected(key_code, (t_obj *)*(main->world->selected));
	rotation_selected(key_code, (t_obj *)(*main->world->selected));
	return (1);
}