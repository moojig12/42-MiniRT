#include "minirt.h"

t_ambient	*parse_amb(t_world *world, char **input)
{
	double	*range;
	t_ambient *new;

	range = alloc_float(0.0, 1.0);
	new = malloc(sizeof(t_ambient));
	// if (index > 2 || index < 1)
	// 	printf("Error\ninvalid input for ambience %i\n", index);
	if (input[1])
	{
		if (ft_range_f(ft_atof(input[1]), range[0], range[1]))
			new->ratio = ft_atof(input[1]);
		else
			exit_err_init("Error\nWrong ambience light ratio\n", 1, world);
	}
	if (input[2])
		pop_color(&new->color, ft_split(input[2], ','));
	else
		exit_err_init("Error\ninvalid input for ambience\n", 1, world);
	if (world->amb != NULL)
		exit_err_init("Error\nToo many args for amb\n", 1, world);
	return (new);
}

t_light	*parse_light(t_light *lig, char **input)
{
	t_light	*new;
	new = malloc(sizeof(t_light));
	if (input[1])
		pop_vec(&new->pos, ft_split(input, ','), NULL);
	else
		printf("Error\nInvalid input for light %i\n", index);
	if (input[2])
	{
		if (ft_range(ft_atof(input), 0.0, 1.0))
			new->brightness = ft_atof(input);
		else
		{
			new->brightness = 0.0;
			printf("Error\nInvalid input for light brightness\n");
		}
	}
	else
		printf("Error\nInvalid input for light %i\n", index);
	if (input[3])
		pop_color(&main->world.light->color, ft_split(input, ','));
	else
		printf("Error\nInvalid input for light %i\n", index);
	ft_lstadd_back_lig_mrt(&lig, new);
	return (lig);
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

t_camera	*parse_cam(t_world *world, char **input)
{
	t_camera	*ret;
	ret = malloc(sizeof(t_camera));
	// if (index < 1 || index > 3)
	// 	printf("Error\nInvalid input for camera %i\n", index);
	if (input[1])
		pop_vec(&ret->pos ,ft_split(input, ','), NULL);
	else
		printf("Error\nInvalid input for camera %i\n", index);
	if (input[2])
		pop_vec(&ret->norm, ft_split(input, ','), alloc_float(-1.0, 1.0));
	else
		printf("Error\nInvalid input for camera %i\n", index);
	if (input[3])
		pop_fov(&ret->fov, input, alloc_int(0, 180));
	else
		printf("Error\nInvalid input for camera %i\n", index);
	if (world->cam != NULL)
		printf("Error\nToo many arg for cam\n"); //add smth here
	return (ret);
}