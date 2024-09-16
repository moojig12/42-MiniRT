#include "minirt.h"

int	check_iden_type(char *input, t_main *main)
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
		parse_light(main, input, index);
	else if (type == SPHERE)
		parse_sphere(main, input, index);
	else if (type == PLANE)
		parse_plane(main, input, index);
	else if (type == CYLINDER)
		parse_cyl(main, input, index);
	else
	{
		perror("Error\ninvalid type");
		return (0);
	}
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
			type = check_iden_type(input[i], main);
		else
			input_par(input[i], main, i, type);
		i++;
	}
}

int	check_par(t_main *main, char *input)
{
	int	type;

	if (!input || !*input)
		return (-1);
	type = check_identifier(main, ft_split(input, ' '));
	return (type);
}

void	parse_world(t_main *main, char **argv)
{
	int	fd;
	char	*input;

	fd = open(argv[1], O_RDONLY);
	input = get_next_line(fd);
	while (input)
	{
		check_par(main, input);
		free(input);
		input = get_next_line(fd);
	}
	if (input)
		free(input);
}
