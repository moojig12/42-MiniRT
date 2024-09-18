#include "minirt.h"

// check if this works!

int	pop_color(t_rgb *rgb, char **input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_range(ft_atof(input[i]), 0, 255))
			perror("Error\nInvalid range");
		i++;
	}
	if (i != 2)
		return (1);
	else
	{
		rgb->r = ft_atoi(input[0]);
		rgb->g = ft_atoi(input[1]);
		rgb->b = ft_atoi(input[2]);
	}
	i = 0;
	while (input[i])
	{
		free(input[i]);
		i++;
	}
	free(input);
	return (0);
}

int	pop_vec(t_vec *pos, char **input, double *range)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (range && !ft_range_f(ft_atof(input[i]), range[0], range[1]))
			perror("Error\nInvalid range");
		i++;
	}
	if (i != 3)
		return (1);
	else
	{
		pos->x = ft_atof(input[0]);
		pos->y = ft_atof(input[1]);
		pos->z = ft_atof(input[2]);
	}
	i = 0;
	while (input[i])
	{
		free(input[i]);
		i++;
	}
	free(input);
	free(range);
	return (0);
}
