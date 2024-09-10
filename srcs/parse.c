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
	return (0);
}

/* int	check_val(char *input, t_main *main, int flag, int type)
{
	
} */

int	check_identifier(t_main *main, char *input)
{
	int	flag;
	int	type;
	int	i;

	i = 0;
	flag = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
		{
			if (flag == 0)
				type = check_iden_type(&input[i], main);
			else
				input_par(&input[i], main, flag, type);
			flag++;
		}
		while (ft_isspace(input[i]))
			i++;
	}
}

int	check_par(t_main *main, char *input)
{
	int	type;

	if (!input || !*input)
		return (-1);
	type = check_identifier(main, input);
	return (type);
}

int	input_par(char *input, t_main *main, int flag, int type)
{
	if (type == AMBIENCE)
		parse_amb(main, input, flag);
	else if (type == CAMERA)
		parse_cam(main, input, flag);
	else if (type == LIGHT)
		parse_light(main, input, flag);
	else if (type == SPHERE)
		parse_sphere(main, input, flag);
	else if (type == PLANE)
		parse_plane(main, input, flag);
	else if (type == CYLINDER)
		parse_cyl(main, input, flag);
	else
		return (1);
}

void	parse_world(t_main *main, char **argv)
{
	int	fd;
	char	*input;
	char	**tokens;

	tokens = NULL;
	fd = open(argv[1], O_RDONLY);
	input = get_next_line(fd);
	while (!input)
	{
		check_par(main, input);
		free(input);
		input = get_next_line(fd);
		// parse
	}
	free(input);
}
