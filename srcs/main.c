#include "minirt.h"

int	close_window(t_main	*main)
{
	exit (0);
}

void	initialize_main(t_main *main)
{

	main->mlx = mlx_init();
	if (main->width == 0)
		mlx_get_screen_size(main->mlx, &main->width, &main->height);
	main->win = mlx_new_window(main->mlx, main->width, main->height, "minirt");
}

int	main(int argc, char **argv)
{
	t_main	*main;

	main = malloc(sizeof(t_main));
	parse_world(main, argc, argv);
	initialize_main(main);
	mlx_hook(main->win, 17, 0, close_window, main);
	mlx_loop(main->mlx);
	return (0);
}