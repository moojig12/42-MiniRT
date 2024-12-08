#include "minirt.h"

void	render_super(t_main *main, int x, int y, t_rgb **output)
{
	t_ray	ray;
	double	offset_x;
	double	offset_y;
	int	sub_y;
	int	sub_x;

	sub_y = 0;
	sub_x = 0;
	while (sub_y < STATIC_SAMPLE)
	{
		while (sub_x < STATIC_SAMPLE)
		{
			offset_x = (double)sub_x / STATIC_SAMPLE;
			offset_y = (double)sub_y / STATIC_SAMPLE;
			ray = gen_ray(main->world->cam, x + offset_x, y + offset_y);
			output[y][x] = color_add(output[y][x], trace_path(main->world, ray, 1));
			sub_x++;
		}
		sub_x = 0;
		sub_y++;
	}
	output[y][x] = color_scalar_div(output[y][x], STATIC_SAMPLE * STATIC_SAMPLE);
	output[y][x] = color_normalize(output[y][x]);
}

void	render_low(t_main *main, int x, int y, t_rgb **output)
{
	t_ray	ray;

	ray = gen_ray_low(main->world->cam, x, y);
	output[y][x] = color_add(output[y][x], trace_path(main->world, ray, 1));
	output[y][x] = color_normalize(output[y][x]);
}
