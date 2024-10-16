/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:13:43 by fjoestin          #+#    #+#             */
/*   Updated: 2024/10/14 22:08:31 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_iden_type(char *input)
{
	if (ft_strcmp(input, "A") == 0)
		return (AMBIENCE);
	if (ft_strcmp(input, "C") == 0)
		return (CAMERA);
	if (ft_strcmp(input, "L") == 0)
		return (LIGHT);
	if (ft_strcmp(input, "pl") == 0)
		return (PLANE);
	if (ft_strcmp(input, "sp") == 0)
		return (SPHERE);
	if (ft_strcmp(input, "cy") == 0)
		return (CYLINDER);
	return (-1);
}

int	input_par(char **input, t_world *world, int type)
{
	if (type == AMBIENCE)
		world->amb = parse_amb(world, input);
	else if (type == CAMERA)
		world->cam = parse_cam(world, input);
	else if (type == LIGHT)
		parse_light(world, world->light, input);
	else if (type == SPHERE)
		parse_sphere(world, input);
	else if (type == PLANE)
		parse_plane(world, input);
	else if (type == CYLINDER)
		parse_cyl(world, input);
	else
		printf("Error\ninvalid type");
	printf("type: %i\n", type);
	return (0);
}

int	check_par(t_world *world, char *input) 
{
	int	type;
	char	**input_matrix;

	if (!input || !*input)
		return (0);
	input_matrix = ft_split(input, ' ');
	printf("input_matrix[0]: %s\n", input_matrix[0]);
	type = check_iden_type(input_matrix[0]);
	printf("type1: %i\n", type);
	if (type != -1 && input_matrix[1])
	{
		input_par(input_matrix, world, type);
		world->objlist = ft_add_obj_lst(type, world, &world->objlist);
	}
	return (type);
}

void	init_world(t_world *world)
{
	world->amb = NULL;
	world->cam = NULL;
	world->light = NULL;
	world->objlist = NULL;
	world->cyl = NULL;
	world->plane = NULL;
	world->sphere = NULL;
}

t_world	*parse_world(t_world *world, char **argv)
{
	int	fd;
	char	*input;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_err_init("failed opening files\n", 1, NULL);
	input = get_next_line(fd);
	init_world(world);
	while (input)
	{
		if (check_par(world, input) == -1)
			exit_err_init("wrong type\n", 1, world);
		free(input);
		input = get_next_line(fd);
	}
	if (input)
		free(input);
	return (world);
}
