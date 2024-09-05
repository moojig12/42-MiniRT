#include "minirt.h"

int	main(void)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 800, 600, "minirt");
	mlx_hook(mlx_win, 0, 0, NULL, NULL);
	return (0);
}