#include "minirt.h"

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
	return (0);
}

int	movement_selected(int key_code, t_obj *selected)
{
	if (key_code == FORWARD)
		move(selected, move_angle(Z_AXIS, 0.25), key_code);
	if (key_code == LEFT)
		move(selected, move_angle(X_AXIS, -0.25), key_code);
	if (key_code == BACK)
		move(selected, move_angle(Z_AXIS, -0.25), key_code);
	if (key_code == RIGHT)
		move(selected, move_angle(X_AXIS, 0.25), key_code);
	if (key_code == UP)
		move(selected, move_angle(Y_AXIS, 0.25), key_code);
	if (key_code == DOWN)
		move(selected, move_angle(Y_AXIS, -0.25), key_code);
	return (0);
}

void	set_selection(t_obj *list, t_main *main, int target)
{
	list = main->world->objlist;
	while (list && list->type != target)
	{
		printf("object checked: %i\n", list->type);
		if (list->type == target)
			printf("FOUND!\n");
		list = list->next;
	}
	main->world->selected = list;
	if (main->world->selected->type == PLANE)
		printf("selection set to PLANE\n");
	if (main->world->selected->type == CYLINDER)
		printf("selection set to CYLINDER\n");
	if (main->world->selected->type == SPHERE)
		printf("selection set to SPHERE\n");
	if (main->world->selected->type == CAMERA)
		printf("selection set to CAMERA\n");
	if (main->world->selected->type == LIGHT)
		printf("selection set to LIGHT\n");
}
