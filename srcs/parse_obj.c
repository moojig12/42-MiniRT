#include "minirt.h"

int	parse_cyl(t_obj *obj, char *input, int index)
{
	/* if (!obj)
		obj = malloc(sizeof(t_cyl)); */
	if (index > 5 || index < 1)
		printf("Error\nInvalid input for cylinder\n");
	if (index == 1)
		pop_vec(&obj->pos, ft_split(input, ','), NULL);
	if (index == 2)
		pop_vec(&obj->norm, ft_split(input, ','), alloc_float(-1.0, 1.0));
	if (index == 3)
		obj->diameter = ft_atof(input);
	if (index == 4)
		obj->height = ft_atof(input);
	if (index == 5)
		pop_color(&obj->material.color, ft_split(input, ','));
	return (0);
}

int	parse_plane(t_obj *obj, char *input, int index)
{
	/* if (!obj)
		obj = malloc(sizeof(t_plane)); */
	if (index > 3 || index < 1)
		return (0);
	if (index == 1)
		pop_vec(&obj->pos, ft_split(input, ','), NULL);
	if (index == 2)
		pop_vec(&obj->norm, ft_split(input, ','), alloc_float(-1.0, 1.0));
	if (index == 3)
		pop_color(&obj->material.color, ft_split(input, ','));
	return (0);
}

int	parse_sphere(t_obj *obj, char *input, int index)
{
	/* if (!obj)
		obj = malloc(sizeof(t_sphere)); */
	if (index > 3 || index < 1)
		return (0);
	if (index == 1)
		pop_vec(&obj->pos, ft_split(input, ','), NULL);
	if (index == 2)
		obj->diameter = ft_atof(input);
	if (index == 3)
		pop_color(&obj->material.color, ft_split(input, ','));
	return (0);
}