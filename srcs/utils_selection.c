#include "minirt.h"

t_selected	discern_nonobject(t_obj *object, t_selected selected)
{
	if (object->type == CAMERA)
	{
		selected.pos = &((t_camera *)object->data)->pos;
		selected.norm = &((t_camera *)object->data)->norm;
		selected.dir = &((t_camera *)object->data)->direction;
		selected.type = CAMERA;
	}
	if (object->type == LIGHT)
	{
		selected.pos = &((t_light *)object->data)->pos;
		selected.norm = NULL;
		selected.type = LIGHT;
	}
	return (selected);
}

t_selected	discern_object(t_obj *object)
{
	t_selected	selected;

	selected.pos = NULL;
	selected.norm = NULL;
	selected.dir = NULL;
	if (object->type == SPHERE)
	{
		selected.pos = &((t_sphere *)object->data)->pos;
		selected.norm = NULL;
		selected.type = SPHERE;
	}
	else if (object->type == CYLINDER)
	{
		selected.pos = &((t_cyl *)object->data)->pos;
		selected.norm = &((t_cyl *)object->data)->norm;
		selected.type = CYLINDER;
	}
	else if (object->type == PLANE)
	{
		selected.pos = &((t_plane *)object->data)->pos;
		selected.norm = &((t_plane *)object->data)->norm;
		selected.type = PLANE;
	}
	else
		selected = discern_nonobject(object, selected);
	return (selected);
}

void	set_next(t_obj *selection)
{
	t_obj	*current;
	int		target;

	target = selection->type;
	current = selection->next;
	while (current && current->type != target)
	{
		printf("object checked: %i\n", current->type);
		if (current->type == selection->type)
			printf("FOUND!\n");
		current = current->next;
	}
	if (!current)
		return ;
	else
		selection = current;
}

void	check_selection_inner(t_main *main, int type)
{
	if (main->world->selected->type == type)
	{
		printf("print next\n");
		set_next(main->world->selected);
	}
	else
		set_selection(main->world->selected, main, type);
}

void	check_selection(int key_code, t_main *main)
{
	if (key_code == OBJ_CAM)
	{
		if (main->world->selected->type == CAMERA)
			printf("Camera already selected\n");
		else
			set_selection(main->world->selected, main, CAMERA);
	}
	else if (key_code == OBJ_LIGHT)
	{
		if (main->world->selected->type == LIGHT)
			printf("Light already selected\n");
		else
			set_selection(main->world->selected, main, LIGHT);
	}
	else if (key_code == OBJ_CYL)
	{
		if (main->world->selected->type == CYLINDER)
			printf("Cylinder already selected\n");
		else
			set_selection(main->world->selected, main, CYLINDER);
	}
	else if (key_code == OBJ_SPHERE)
	{
		if (main->world->selected->type == SPHERE)
			printf("Sphere already selected\n");
		else
			set_selection(main->world->selected, main, SPHERE);
	}
	else if (key_code == OBJ_PLANE)
	{
		if (main->world->selected->type == PLANE)
			printf("Plane already selected\n");
		else
			set_selection(main->world->selected, main, PLANE);
	}
}
