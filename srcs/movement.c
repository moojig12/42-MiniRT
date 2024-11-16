#include "minirt.h"

int	move_forward(t_main *main)
{
	main->world->cam->pos.z++;
	return (0);
}

int	move_left(t_main *main)
{
	main->world->cam->pos.x--;
	return (0);
}

int	move_back(t_main *main)
{
	main->world->cam->pos.z--;
	return (0);
}

int	move_right(t_main *main)
{
	main->world->cam->pos.x++;
	return (0);
}

int	move_up(t_main *main)
{
	main->world->cam->pos.y++;
	return (0);
}

int	move_down(t_main *main)
{
	main->world->cam->pos.y--;
	return (0);
}

int	rotate_left(t_main *main)
{
	t_vec	rotated_vec;
	double	theta;

	theta = -5 * (PI / 180);
	double cos_theta = cos(theta);
	double sin_theta = sin(theta);

	rotated_vec.x = main->world->cam->direction.x * cos_theta + main->world->cam->direction.z * sin_theta;
	rotated_vec.y = main->world->cam->direction.y;
	rotated_vec.z = -main->world->cam->direction.x * sin_theta + main->world->cam->direction.z * cos_theta;
	main->world->cam->direction = rotated_vec;

	return (0);
}

int	rotate_right(t_main *main)
{
	t_vec	rotated_vec;
	double	theta;

	theta = 5 * (PI / 180);
	double cos_theta = cos(theta);
	double sin_theta = sin(theta);

	rotated_vec.x = main->world->cam->direction.x * cos_theta + main->world->cam->direction.z * sin_theta;
	rotated_vec.y = main->world->cam->direction.y;
	rotated_vec.z = -main->world->cam->direction.x * sin_theta + main->world->cam->direction.z * cos_theta;

	main->world->cam->direction = rotated_vec;

	return (0);
}

int	movement(int key_code, t_main *main)
{
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
	return (1);
}