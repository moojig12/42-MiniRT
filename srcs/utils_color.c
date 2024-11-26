#include "../minirt.h"

t_rgb	color_normalize(t_rgb color)
{
	t_rgb	ret;

	ret.r = (double)fmin(color.r, 1.0);
	ret.g = (double)fmin(color.g, 1.0);
	ret.b = (double)fmin(color.b, 1.0);

	return (ret);
}

t_rgb	ret_color(double r, double g, double b)
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

t_rgb color_multiply(t_rgb a, t_rgb b)
{
    return ret_color(a.r * b.r, a.g * b.g, a.b * b.b);
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

int	pack_color(t_rgb color)
{
	int	r;
	int	g;
	int	b;
	int	t;

	r = (int)(255.0 * color.r);
	g = (int)(255.0 * color.g);
	b = (int)(255.0 * color.b);
	t = 255;

	return (t << 24 | r << 16 | g << 8 | b);
}
