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

int	input_par(char *input, t_main *main, int index, int type)
{
	if (type == AMBIENCE)
		parse_amb(main, input, index);
	else if (type == CAMERA)
		parse_cam(main, input, index);
	else if (type == LIGHT)
	{
		parse_light(main, input, index);
	}
	else if (type == SPHERE)
	{
		parse_sphere(&main->world->obj[type - 3], input, index);
	}
	else if (type == PLANE)
	{
		parse_plane(&main->world->obj[type - 3], input, index);
	}
	else if (type == CYLINDER)
	{
		parse_cyl(&main->world->obj[type - 3], input, index);
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
	type = 0;
	while (input[i] && type != -1)
	{
		if (i == 0)
			type = check_iden_type(input[i]);
		else
			input_par(input[i], main, i, type);
		i++;
	}
	return (type);
}

int	check_par(t_main *main, char *input) // is this function necessary?
{
	int	type;

	if (!input || !*input)
		return (0);
	type = check_identifier(main, ft_split(input, ' '));
	return (type);
}

void	parse_world(t_main *main, char **argv)
{
	int	fd;
	char	*input;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (exit_err("failed opening files\n", 1));
	input = get_next_line(fd);
	main->world->amb = malloc(sizeof(t_ambient)); // do I need to do this here?
	main->world->light = malloc(sizeof(t_light));// do I need to do this here?
	main->world->cam = malloc(sizeof(t_camera)); // do I need to do this here?
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
