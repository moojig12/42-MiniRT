/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 08:14:29 by root              #+#    #+#             */
/*   Updated: 2024/12/19 16:04:53 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	close_window(t_main	*main)
{
	free_main(main);
	exit (0);
}

void	sub_main_init(t_main *main)
{
	main->world->cam->width = main->width;
	main->world->cam->height = main->height;
	main->world->cam->norm = vec(0, 1, 0, 0);
	if (main->world->light)
		main->world->light->brightness *= 20;
	main->render_switch = LOW;
}

void	initialize_main(t_main *main, t_world *world)
{
	int	y;

	main->width = 800;
	main->height = 600;
	main->world = world;
	main->mlx = mlx_init();
	if (main->mlx)
		main->win = mlx_new_window(main->mlx, 800, 600, "minirt");
	else
	{
		printf("MLX not initialized properly\n");
		exit(0);
	}
	main->img = mlx_new_image(main->mlx, main->width, main->height);
	main->addr = mlx_get_data_addr(main->img, \
		&main->bits_per_pixel, &main->line_length, &main->endian);
	sub_main_init(main);
	main->output = (t_rgb **)calloc(world->cam->height + 1, sizeof(t_rgb *));
	y = 0;
	while (y < world->cam->height)
	{
		main->output[y] = (t_rgb *)calloc(world->cam->width + 1, sizeof(t_rgb));
		y++;
	}
	main->world->selected = NULL;
}

int	main(int argc, char **argv)
{
	t_main	*main;
	t_world	*world;

	if (argc < 2 || check_file(argv[1]))
		return (printf("Meow"));
	world = malloc(sizeof(t_world));
	world = parse_world(world, argv);
	main = malloc(sizeof(t_main));
	if (!main)
		return (1);
	initialize_main(main, world);
	main_pipeline(main);
	return (0);
}
