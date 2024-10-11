#include "minirt.h"

int	check_iden_type(char *input)
{
	if (ft_strcmp(input, "A"))
		return (AMBIENCE);
	if (ft_strcmp(input, "C"))
		return (CAMERA);
	if (ft_strcmp(input, "L"))
		return (LIGHT);
	if (ft_strcmp(input, "pl"))
		return (PLANE);
	if (ft_strcmp(input, "sp"))
		return (SPHERE);
	if (ft_strcmp(input, "cy"))
		return (CYLINDER);
	return (-1);
}

int	input_par(char **input, t_world *world, int index, int type)
{
	if (type == AMBIENCE)
		world->amb = parse_amb(main, input);
	else if (type == CAMERA)
		world->cam = parse_cam(main, input);
	else if (type == LIGHT)
		world->light = parse_light(&world, input);
	else if (type == SPHERE)
		world->sphere = parse_sphere(&world, input);
	else if (type == PLANE)
		world->plane = parse_plane(&world, input);
	else if (type == CYLINDER)
		world->cyl = parse_cyl(&world, input);
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
	type = check_iden_type(input[0])
	if (type != -1 && input[1])
		input_par(input, main->world, type);
	return (type);
}

int	check_par(t_main *main, char *input) // is this function necessary?
{
	int	type;

	if (!input || !*input)
		return (0);
	type = check_identifier(main, ft_split(input, ' '));
	// add to obj list here
	main->world->objlist = ft_add_obj_lst(type, main->world);
	return (type);
}

int	init_world(t_main *main)
{
	main->world = malloc(sizeof(t_world));
	main->world->amb = NULL;
	main->world->cam = NULL;
	main->world->light = NULL;
	main->world->objlist = NULL;
	main->world->cyl = NULL;
	main->world->plane = NULL;
	main->world->sphere = NULL;
}

void	parse_world(t_main *main, char **argv)
{
	int	fd;
	char	*input;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (exit_err("failed opening files\n", 1));
	input = get_next_line(fd);
	init_world(main);
	while (input)
	{
		if (check_par(main, input) == -1)
			return (exit_err("wrong type\n", 1));
		free(input);
		input = get_next_line(fd);
	}
	if (input)
		free(input);
}
