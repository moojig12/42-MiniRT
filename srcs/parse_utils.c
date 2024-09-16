#include "minirt.h"

// check if this works!

int	pop_color(t_rgb *rgb, char **input)
{
	int	i;

	i = 0;
	while (input[i])
		i++;
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
	}
	free(input);
	return (0);
}

