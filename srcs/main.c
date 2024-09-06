#include "minirt.h"

int	main(void)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 800, 600, "minirt");
	printf("%p", mlx_win);
	return (0);
}