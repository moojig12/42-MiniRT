#include "minirt.h"

int	close_window(t_main	*main)
{
	free(main);
	exit (0);
}

void	initialize_main(t_main *main, t_world *world)
{
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
		printf("why isnt it working\n");
		exit(0);
	}
	main->width = 800;
	main->height = 600;
	main->world->cam->width = 800;
	main->world->cam->height = 600;
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