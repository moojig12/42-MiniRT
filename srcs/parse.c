#include "minirt.h"

int	check_par(char *input, char **tokens)
{
	char	*temp;
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!input || !*input)
		return (-1);
	temp = input;
	while (*temp)
	{
		if (!ft_isspace(*temp))
		{
			tokens[j] = get_value(&temp);
			// Finish making tokenizer!!!
		}
	}
	return (0);
}
// Finish Parser by 11th!!!
int	input_par(t_main *main, char *input, int type)
{
	if (type == AMBIENCE)
		parse_amb();
	else if (type == CAMERA)
		parse_cam();
	else if (type == LIGHT)
		parse_light();
	else if (type == SPHERE)
		parse_sphere();
	else if (type == PLANE)
		parse_plane();
	else if (type == CYLINDER)
		parse_cyl();
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
		input_par(main, input, check_par(input, tokens));
		free(input);
		input = get_next_line(fd);
		// parse
	}
	free(input);
}
