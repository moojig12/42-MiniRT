#include "minirt.h"

double	get_angle(t_vec	movement, t_vec norm)
{
	double	cos_theta;

	cos_theta = vec_dot(movement, norm);
	return (acos(cos_theta));
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
}

int	move(t_obj *obj, t_vec	movement, int movement_code)
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
		t_vec	directed;
			// Translate movement into angle
		directed = movement_rotation(movement, movement_code);
			// Rotate cam->direction and save to moved_vec
		moved_vec = matrix_rotation(*selected.dir, directed);
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
		move(selected, move_angle(Z_AXIS, 1), key_code);
	if (key_code == LEFT)
		move(selected, move_angle(X_AXIS, -1), key_code);
	if (key_code == BACK)
		move(selected, move_angle(Z_AXIS, -1), key_code);
	if (key_code == RIGHT)
		move(selected, move_angle(X_AXIS, 1), key_code);
	if (key_code == UP)
		move(selected, move_angle(Y_AXIS, 1), key_code);
	if (key_code == DOWN)
		move(selected, move_angle(Y_AXIS, -1), key_code);
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
	// main->world->selected = base_selection;
	if ((*main->world->selected)->type == PLANE)
		printf("selection set to PLANE\n");
	if ((*main->world->selected)->type == CYLINDER)
		printf("selection set to CYLINDER\n");
	if ((*main->world->selected)->type == SPHERE)
		printf("selection set to SPHERE\n");
	if ((*main->world->selected)->type == CAMERA)
		printf("selection set to CAMERA\n");
	if ((*main->world->selected)->type == LIGHT)
		printf("selection set to LIGHT\n");
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
			output_color = pack_color(output[y][x].r, output[y][x].g, output[y][x].b);
			mlx_pixel_put(main->mlx, main->win, x, y, output_color);
			x++;
		}
		y++;
	}
}

void	check_selection(int key_code, t_main *main)
{
	if (key_code == OBJ_CAM)
	{
		if ((*main->world->selected)->type == CAMERA)
			printf("Camera already selected\n");
		else
			set_selection(main->world->selected, main, CAMERA);
	}
	else if (key_code == OBJ_LIGHT)
	{
		if ((*main->world->selected)->type == LIGHT)
			printf("Light already selected\n");
		else
			set_selection(main->world->selected, main, LIGHT);
	}
	else if (key_code == OBJ_CYL)
	{
		if ((*main->world->selected)->type == CYLINDER)
			printf("Cylinder already selected\n");
		else
			set_selection(main->world->selected, main, CYLINDER);
	}
	else if (key_code == OBJ_SPHERE)
	{
		if ((*main->world->selected)->type == SPHERE)
			printf("Sphere already selected\n");
		else
			set_selection(main->world->selected, main, SPHERE);
	}
	else if (key_code == OBJ_PLANE)
	{
		if ((*main->world->selected)->type == PLANE)
			printf("Plane already selected\n");
		else
			set_selection(main->world->selected, main, PLANE);
	}
}

int	movement(int key_code, t_main *main)
{
	int		type;

	printf("keycode: %i\n", key_code);
	if (!main->world->selected)
	{
		main->world->selected = malloc(sizeof(t_obj *));
		set_selection(main->world->selected, main, CAMERA);
		printf("mallocated\n");
	}
	type = (*main->world->selected)->type;
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