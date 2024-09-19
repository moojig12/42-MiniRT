#include "minirt.h"

int	parse_cyl(t_main *main, char *input, int index)
{
	if (index > 5 || index < 1)
		perror("Error\nInvalid input for cylinder");
	if (index == 1)
		pop_vec(&main->world.cyl->pos, ft_split(input, ','), NULL);
	if (index == 2)
		pop_vec(&main->world.cyl->norm, ft_split(input, ','), alloc_float(-1.0, 1.0));
	if (index == 3)
		main->world.cyl->diameter = ft_atof(input);
	if (index == 4)
		main->world.cyl->height = ft_atof(input);
	if (index == 5)
		pop_color(&main->world.cyl->color, ft_split(input, ','));
	return (0);
}

int	parse_plane(t_main *main, char *input, int index)
{
	if (index > 3 || index < 1)
		return (0);
	if (index == 1)
		pop_vec(&main->world.plane->pos, ft_split(input, ','), NULL);
	if (index == 2)
		pop_vec(&main->world.plane->norm, ft_split(input, ','), alloc_float(-1.0, 1.0));
	if (index == 3)
		pop_color(&main->world.plane->color, ft_split(input, ','));
}

int	parse_sphere(t_main *main, char *input, int index)
{
	if (index > 3 || index < 1)
		return (0);
	if (index == 1)
		pop_vec(&main->world.sphere->pos, ft_split(input, ','), NULL);
	if (index == 2)
		main->world.sphere->diameter = ft_atof(input);
	if (index == 3)
		pop_color(&main->world.sphere->color, ft_split(input, ','));
}