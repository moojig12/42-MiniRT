#include "minirt.h"

int	parse_cyl(t_cyl *cyl, char *input, int index)
{
	if (!cyl)
		cyl = malloc(sizeof(t_cyl));
	if (index > 5 || index < 1)
		printf("Error\nInvalid input for cylinder\n");
	if (index == 1)
		pop_vec(&cyl->pos, ft_split(input, ','), NULL);
	if (index == 2)
		pop_vec(&cyl->norm, ft_split(input, ','), alloc_float(-1.0, 1.0));
	if (index == 3)
		cyl->diameter = ft_atof(input);
	if (index == 4)
		cyl->height = ft_atof(input);
	if (index == 5)
		pop_color(&cyl->color, ft_split(input, ','));
	return (0);
}

int	parse_plane(t_plane *plane, char *input, int index)
{
	if (!plane)
		plane = malloc(sizeof(t_plane));
	if (index > 3 || index < 1)
		return (0);
	if (index == 1)
		pop_vec(&plane->pos, ft_split(input, ','), NULL);
	if (index == 2)
		pop_vec(&plane->norm, ft_split(input, ','), alloc_float(-1.0, 1.0));
	if (index == 3)
		pop_color(&plane->color, ft_split(input, ','));
	return (0);
}

int	parse_sphere(t_sphere *sphere, char *input, int index)
{
	if (!sphere)
		sphere = malloc(sizeof(t_sphere));
	if (index > 3 || index < 1)
		return (0);
	if (index == 1)
		pop_vec(&sphere->pos, ft_split(input, ','), NULL);
	if (index == 2)
		sphere->diameter = ft_atof(input);
	if (index == 3)
		pop_color(&sphere->color, ft_split(input, ','));
	return (0);
}