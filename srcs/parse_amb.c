#include "minirt.h"

int	parse_amb(t_main *main, char *input, int index)
{
	if (index > 2 || index < 1)
		perror("Error\ninvalid input for ambience");
	if (index == 1)
	{
		if (ft_atof(input) >= 0 && ft_atof(input) >= 1)
			main->world.amb->ratio = ft_atof(input);
		else
			perror("Error\nWrong ambience light ratio");
	}
	else if (index == 2)
		pop_color(&main->world.amb->color, ft_split(input, ','));
}

int	parse_light(t_main *main, char *input, int index)
{
	if (index > 3 || index < 1)
		perror("Error\nInvalid input for light");
	if (index == 1)
		pop_vec(&main->world.light->pos, ft_split(input, ','), NULL);
	if (index == 2)
	{
		if (ft_range(ft_atof(input), 0.0, 1.0))
			main->world.light->brightness = ft_atof(input);
		else
		{
			main->world.light->brightness = 0.0;
			perror("Error\nInvalid input for light brightness");
		}
	}
	if (index == 3)
		pop_color(&main->world.light->color, ft_split(input, ','));
}

int	pop_fov(int *fov, char *input, int *range)
{
	if (!input)
		return (0);
	if (ft_range(ft_atoi(input), range[0], range[1]))
		*fov = ft_atoi(input);
	free(range);
}

int	parse_cam(t_main *main, char *input, int index)
{
	if (index < 1 || index > 3)
		perror("Error\nInvalid input for camera");
	if (index == 1)
		pop_vec(&main->world.cam->pos ,ft_split(input, ','), NULL);
	if (index == 2)
		pop_vec(&main->world.cam->norm, ft_split(input, ','), alloc_float(-1.0, 1.0));
	if (index == 3)
		pop_fov(&main->world.cam->fov, input, alloc_int(0, 180));
}