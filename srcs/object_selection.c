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
