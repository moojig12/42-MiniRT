#include "minirt.h"

// check if this works!

int	pop_color(t_rgb *rgb, char **input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_range(ft_atof(input[i]), 0, 255))
		{
			printf("Error\nInvalid range for color");
			exit (0);
		}
		i++;
	}
	if (i != 3)
		return (1);
	else
	{
		rgb->r = (double)ft_atoi(input[0]) / 255;
		rgb->g = (double)ft_atoi(input[1]) / 255;
		rgb->b = (double)ft_atoi(input[2]) / 255;
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

int	pop_vec(t_vec *pos, char **input, double *range, double type)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (range && !ft_range_f(ft_atof(input[i]), range[0], range[1]))
		{
			printf("Error\nInvalid range for vec\n");
			printf("This is outside the range (%f, %f): %f", range[0], range[1],ft_atof(input[i]));
			exit(0);
		}
		i++;
	}
	if (i != 3)
		return (1);
	else
	{
		printf("1:%s 2:%s 3:%s\n", input[0], input[1], input[2]);
		pos->x = ft_atof(input[0]);
		pos->y = ft_atof(input[1]);
		pos->z = ft_atof(input[2]);
		pos->w = type;
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
int	pop_fov(int *fov, char *input, int *range)
{
	if (!input)
		return (0);
	if (ft_range(ft_atoi(input), range[0], range[1]))
		*fov = ft_atoi(input);
	free(range);
	return (0);
}