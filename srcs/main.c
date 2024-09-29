#include "minirt.h"

int	close_window(t_main	*main)
{
	free(main);
	exit (0);
}

void	initialize_main(t_main *main)
{
	main->mlx = mlx_init();
	if (main->width == 0)
		mlx_get_screen_size(main->mlx, &main->width, &main->height);
	main->win = mlx_new_window(main->mlx, 800, 600, "minirt");
	main->world.cam->width = 800;
	main->world.cam->height = 600;
}

int	main(int argc, char **argv)
{
	t_main	*main;

	if (argc < 2)
		printf("Meow");
	main = malloc(sizeof(t_main));
	parse_world(main, argv);
	initialize_main(main);

	main_pipeline(main);
	return (0);
}