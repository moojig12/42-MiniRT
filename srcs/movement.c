#include "minirt.h"

int	move_forward(t_main *main)
{
	main->world->cam->pos = matrix_translation(main->world->cam->pos, vec(0, 0, 2, 1));
	return (0);
}

int	move_left(t_main *main)
{
	print_vec("before:", main->world->cam->pos);
	main->world->cam->pos = matrix_translation(main->world->cam->pos, vec(-2, 0, 0, 1));
	print_vec("after:", main->world->cam->pos);
	return (0);
}

int	move_back(t_main *main)
{
	main->world->cam->pos = matrix_translation(main->world->cam->pos, vec(0, 0, -2, 1));
	return (0);
}

int	move_right(t_main *main)
{
	main->world->cam->pos = matrix_translation(main->world->cam->pos, vec(2, 0, 0, 1));
	return (0);
}

int	move_up(t_main *main)
{
	main->world->cam->pos = matrix_translation(main->world->cam->pos, vec(0, 2, 0, 1));
	return (0);
}

int	move_down(t_main *main)
{
	main->world->cam->pos = matrix_translation(main->world->cam->pos, vec(0, -2, 0, 1));
	return (0);
}

int	rotate_left(t_main *main)
{
	t_vec	rotated_vec;

	rotated_vec = matrix_rotation(main->world->cam->direction, vec(0, -0.2, 0, 0));
	main->world->cam->direction = rotated_vec;

	return (0);
}

int	rotate_right(t_main *main)
{
	t_vec	rotated_vec;

	print_vec("before", main->world->cam->direction);
	rotated_vec = matrix_rotation(main->world->cam->direction, vec(0, 0.2, 0, 0));
	main->world->cam->direction = rotated_vec;
	print_vec("after", main->world->cam->direction);

	return (0);
}

int	rotate_cylinder(t_cyl *cyl, t_vec rotation)
{
	t_vec	rotated_vec;

	rotated_vec = matrix_rotation(cyl->norm, rotation);
	cyl->norm = rotated_vec;

	return (0);
}

int	movement(int key_code, t_main *main)
{
	// printf("keycode: %i\n", key_code);
	if (key_code == ESC_WIN)
		close_window(main);
	if (key_code == FORWARD)
		move_forward(main);
	if (key_code == LEFT)
		move_left(main);
	if (key_code == BACK)
		move_back(main);
	if (key_code == RIGHT)
		move_right(main);
	if (key_code == UP)
		move_up(main);
	if (key_code == DOWN)
		move_down(main);
	if (key_code == ROTATE_LEFT)
		rotate_left(main);
	if (key_code == ROTATE_RIGHT)
		rotate_right(main);
	if (key_code == 105)
		rotate_cylinder(main->world->cyl, vec(0.1, 0, 0 ,0));
	if (key_code == 106)
		rotate_cylinder(main->world->cyl, vec(0, -0.1, 0 ,0));
	if (key_code == 107)
		rotate_cylinder(main->world->cyl, vec(-0.1, 0, 0 ,0));
	if (key_code == 108)
		rotate_cylinder(main->world->cyl, vec(0, 0.1, 0 ,0));
	if (key_code == 117)
		rotate_cylinder(main->world->cyl, vec(0, 0, -0.1, 0));
	if (key_code == 111)
		rotate_cylinder(main->world->cyl, vec(0, 0, 0.1, 0));
	return (1);
}