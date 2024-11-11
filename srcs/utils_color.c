#include "minirt.h"

t_rgb	color_normalize(t_rgb color)
{
	t_rgb	ret;

	ret.r = (int)fmin(color.r, 255);
	ret.g = (int)fmin(color.g, 255);
	ret.b = (int)fmin(color.b, 255);

	return (ret);
}

t_rgb	ret_color(int r, int g, int b)
{
	t_rgb	ret;

	ret.r = r;
	ret.g = g;
	ret.b = b;

	return (ret);
}

t_rgb	color_add(t_rgb a, t_rgb b)
{
	t_rgb	ret;

	ret.r = a.r + b.r;
	ret.g = a.g + b.g;
	ret.b = a.b + b.b;

	return (ret);
}

t_rgb	color_sub(t_rgb a, t_rgb b)
{
	t_rgb	ret;

	ret.r = a.r - b.r;
	ret.g = a.g - b.g;
	ret.b = a.b - b.b;

	return (ret);
}

t_rgb	color_multiply(t_rgb a, t_rgb b)
{
	t_rgb	ret;

	ret.r = a.r * b.r;
	ret.g = a.g * b.g;
	ret.b = a.b * b.b;

	return (ret);
}

t_rgb	color_scalar(t_rgb a, double scalar)
{
	t_rgb	ret;

	ret.r = a.r * scalar;
	ret.g = a.g * scalar;
	ret.b = a.b * scalar;

	return (ret);
}

t_rgb	color_scalar_div(t_rgb a, double scalar)
{
	t_rgb	ret;

	ret.r = a.r / scalar;
	ret.g = a.g / scalar;
	ret.b = a.b / scalar;

	return (ret);
}

int	pack_color(int r, int g, int b)
{
	int	t;

	t = 255;
	return (t << 24 | r << 16 | g << 8 | b);
}
