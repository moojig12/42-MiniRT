#include "minirt.h"

t_cyl	*parse_cyl(t_world *world, char **input)
{
	t_cyl *new;
	new = malloc(sizeof(t_cyl)); 
	// if (index > 5 || index < 1)
		// printf("Error\nInvalid input for cylinder\n");
	if (input[1])
		pop_vec(&obj->pos, ft_split(input, ','), NULL);
	if (input[2])
		pop_vec(&obj->norm, ft_split(input, ','), alloc_float(-1.0, 1.0));
	if (input[3])
		obj->diameter = ft_atof(input);
	if (input[4])
		obj->height = ft_atof(input);
	if (input[5])
		pop_color(&obj->color, ft_split(input, ','));
	ft_lstadd_back_cyl_mrt(&world->cyl, new);
	return (world->cyl);
}

int	parse_plane(t_world *world, char **input)
{
	t_plane	*new;
	new = malloc(sizeof(t_plane));
	// if (index > 3 || index < 1)
		// return (0);
	if (input[1])
		pop_vec(&new->pos, ft_split(input, ','), NULL);
	if (input[2])
		pop_vec(&obj->norm, ft_split(input, ','), alloc_float(-1.0, 1.0));
	if (input[3])
		pop_color(&obj->material.color, ft_split(input, ','));
	return (0);
}

int	parse_sphere(t_world *world, char **input)
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