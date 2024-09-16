#include "minirt.h"

int	pop_coords(t_vec *pos, char **input)
{
	int	i;

	i = 0;
	while (input[i])
		i++;
	if (i != 2)
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
	}
	free(input);
	return (0);
}

int	pop_norm(t_vec *norm, char *input)
{
	return (0);
}

int	parse_cam(t_main *main, char *input, int index)
{
	if (index < 1 || index > 3)
		perror("Error\nInvalid input for camera");
	if (index == 1)
		pop_coords(&main->world.cam->pos ,ft_split(input, ','));
	if (index == 2)
		pop_norm(&main->world.cam->norm, ft_split(input, ','));
	if (index == 3)
		pop_fov(input);
}