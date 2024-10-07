#include "minirt.h"

int	check_iden_type(char *input)
{
	if (!ft_strncmp(input, "A", 1))
		return (AMBIENCE);
	if (!ft_strncmp(input, "C", 1))
		return (CAMERA);
	if (!ft_strncmp(input, "L", 1))
		return (LIGHT);
	if (ft_strlen(input) >= 2)
	{
		if (!ft_strncmp(input, "pl", 2))
			return (PLANE);
		if (!ft_strncmp(input, "sp", 2))
			return (SPHERE);
		if (!ft_strncmp(input, "cy", 2))
			return (CYLINDER);
	}
	return (-1);
}

int	input_par(char *input, t_main *main, int index, int type)
{
	if (type == AMBIENCE)
		parse_amb(main, input, index);
	else if (type == CAMERA)
		parse_cam(main, input, index);
	else if (type == LIGHT)
	{
		// main->world->obj[type - 3].type = type;
		parse_light(main, input, index);
	}
	else if (type == SPHERE)
	{
		// main->world->obj[type - 3].type = type;
		parse_sphere(main->world->sphere, input, index);
	}
	else if (type == PLANE)
	{
		// main->world->obj[type - 3].type = type;
		parse_plane(main->world->plane, input, index);
	}
	else if (type == CYLINDER)
	{
		// main->world->obj[type - 3].type = type;
		parse_cyl(main->world->cyl, input, index);
	}
	else
		printf("Error\ninvalid type");
	return (0);
}

int	check_identifier(t_main *main, char **input)
{
	int	type;
	int	i;

	if (!input)
		return (0);
	i = 0;
	while (input[i])
	{
		if (i == 0)
			type = check_iden_type(input[i]);
		else
			input_par(input[i], main, i, type);
		i++;
	}
	return (0);
}

int	check_par(t_main *main, char *input)
{
	int	type;

	if (!input || !*input)
		return (-1);
	type = check_identifier(main, ft_split(input, ' '));
	return (type);
}

void	append_node(t_world *base, t_obj *node)
{
	t_obj	*temp;

	if (base->obj == NULL)
		base->obj = node;
	else
	{
		temp = base->obj;
		while (temp->next)
			temp = temp->next;
		temp->next = node;
	}
}

void	parse_world(t_main *main, char **argv)
{
	int	fd;
	int	i;
	char	*input;
	t_obj	*object;

	fd = open(argv[1], O_RDONLY);
	input = get_next_line(fd);
	main->world->obj = NULL;
	main->world->object_num = 4;
	main->world->amb = malloc(sizeof(t_ambient));
	main->world->light = malloc(sizeof(t_light));
	main->world->cam = malloc(sizeof(t_camera));
	main->world->sphere = malloc(sizeof(t_sphere));
	main->world->cyl = malloc(sizeof(t_cyl));
	main->world->plane = malloc(sizeof(t_plane));
	while (input)
	{
		check_par(main, input);
		free(input);
		input = get_next_line(fd);
	}
	if (input)
		free(input);
	
	i = 0;
	while (i < 3)
	{
		object = malloc(sizeof(t_obj));
		if (i == 0)
		{
			object->type = SPHERE;
			object->data = (void *)main->world->sphere;
		}
		if (i == 1)
		{
			object->type = PLANE;
			object->data = (void *)main->world->plane;
		}
		if (i == 2)
		{
			object->type = CYLINDER;
			object->data = (void *)main->world->cyl;
		}
		object->next = NULL;
		append_node(main->world, object);
		printf("object type prase:%i\nobject pointer: %p\n", object->type, main->world->obj);
		object = NULL;
		i++;
	}
	t_obj	*test;

	test = main->world->obj;
	while (test)
	{
		printf("world node %i: %p\n", test->type, test->data);
		test = test->next;
	}
}
