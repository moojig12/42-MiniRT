#include "minirt.h"

int	close_window(t_main	*main)
{
	free_world(main->world);
	mlx_clear_window(main->mlx, main->win);
	mlx_destroy_window(main->mlx, main->win);
	//free(main);
	exit (0);
}

void	initialize_main(t_main *main, t_world *world)
{
	int	y;

	y = 0;
	main->world = world;
	main->mlx = mlx_init();
	if (main->mlx)
	{
		/* if (main->width == 0)
			mlx_get_screen_size(main->mlx, &main->width, &main->height); */
		main->win = mlx_new_window(main->mlx, 800, 600, "minirt");
	}
	else
	{
		printf("MLX not initialized properly\n");
		exit(0);
	}
	main->width = 800;
	main->height = 600;

	main->world->cam->width = main->width;
	main->world->cam->height = main->height;
	main->render_switch = 0;
	main->world->cam->norm = vec(0, 1, 0, 0);
	main->output = (t_rgb **)calloc(world->cam->height + 1, sizeof(t_rgb *));
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
	main = malloc(sizeof(t_main));// change, initialize after world and just pass world done for the next func
	initialize_main(main, world);

	main_pipeline(main);
	return (0);
}