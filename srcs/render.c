#include "minirt.h"

void	loop(t_main *main)
{
	mlx_hook(main->win, 17, 0, close_window, main);
	mlx_loop(main->mlx);
}

t_rgb	trace(t_ray ray, int depth, t_world world)
{
	t_intersection	intersection;
	t_ray	new_ray;

	if (depth >= MAXDEPTH)
		return (color(0, 0, 0));
	intersection = check_intersection(ray, world);
	if (!intersection.hit)
		return (color(0, 0, 0));
	// continue from newray and get direction
	new_ray.origin = last_hit;

	// implement BRDF

	// Trace light source recursively
	incoming = trace(new_ray, depth + 1);
	return (emission + (BRDF * incoming * cos_theta / p));
}

t_rgb	raytrace(t_world world)
{
	t_ray	ray;
	int		depth;

	// generate ray according to FOV and Screen angle
	// ray = (assign origin and dest);

	depth = 0;
	return (trace(ray, depth, world));
}

void	render(t_main *main, t_world world)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	// generate rays for each pixel and incrementally add to pixel
	while (1)
	{
		while (j < main->height)
		{
			while (i < main->width)
			{
				//	generate ray and save (to screen?)
				//		screen.color (use dot function) raytrace(world);
				i++;
			}
			i = 0;
			j++;
		}
		i = 0;
	}
}

int	main_pipeline(t_main *main)
{
	render(main, main->world);

	loop(main);
}