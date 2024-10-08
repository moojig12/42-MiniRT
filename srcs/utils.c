#include "minirt.h"

// Function expects proper input! No '+' allowed
double	ft_atof(char *str)
{
	double	result;
	double	fraction;
	int	has_fraction;
	int	sign;

	result = 0.0;
	fraction = 1.0;
	has_fraction = 0;
	if (!str)
		return (0.0);
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else
		sign = 1;
	while (*str)
	{
		if (ft_isdigit(*str))
		{
			if (has_fraction)
			{
				fraction *= 0.1;
				result += fraction * (*str - '0');
			}
			else
				result = result * 10.0 + (*str - '0');
		}
		else if (*str == '.')
		{
			if (has_fraction)
				break;
			has_fraction = 1;
		}
		else
			break ;
		str++;
	}
	return (result * sign);
}

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 12 && c <= 15))
		return (1);
	else
		return (0);
}

int	*alloc_int(int a, int b)
{
	int	*result;

	result = malloc(2 * (sizeof(int)));
	if (!result)
		return (NULL);
	result[0] = a;
	result[1] = b;
	return (result);
}

double	*alloc_float(double a, double b)
{
	double	*result;

	result = malloc(2 * (sizeof(double)));
	if (!result)
		return (NULL);
	result[0] = a;
	result[1] = b;
	return (result);
}

// returns 1 if within range. 0 if outside of range
int	ft_range(int num, int min, int max)
{
	if (num >= min || num <= max)
		return (1);
	else
		return (0);
}

t_vec	vec(double x, double y, double z)
{
	t_vec	output;

	output.x = x;
	output.y = y;
	output.z = z;
	return (output);
}

// returns 1 if within range. 0 if outside of range
int	ft_range_f(double num, double min, double max)
{
	if (num >= min || num <= max)
		return (1);
	else
		return (0);
}

int pack_color(int r, int g, int b)
{
	int	t;

	t = 255;
	return (t << 24 | r << 16 | g << 8 | b);
}

// addition operation for two vectors
t_vec add(t_vec a, t_vec b)
{
	t_vec ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	return (ret);
}

t_vec	subtract(t_vec a, t_vec b)
{
	t_vec ret;

	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return (ret);
}

double	dot(t_vec a, t_vec b)
{
	double ret;

	ret = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	return (ret);
}

t_rgb	color_add(t_rgb a, t_rgb b)
{
	t_rgb	ret;

	ret.r = (a.r + b.r > 255) ? 255 : a.r + b.r;
	ret.g = (a.g + b.g > 255) ? 255 : a.g + b.g;
	ret.b = (a.b + b.b > 255) ? 255 : a.b + b.b;
	return (ret);
}

t_rgb	color_multiply(t_rgb a, t_rgb b)
{
	t_rgb result;

	result.r = a.r * b.r;
	result.g = a.g * b.g;
	result.b = a.b * b.b;
	return (result);
}

t_rgb	color_scalar(t_rgb color, double scalar)
{
	int r;
	int g;
	int b;

	r = (int)((int)(color.r) * scalar);
	g = (int)((int)(color.g) * scalar);
	b = (int)((int)(color.b) * scalar);

	r = (r > 255) ? 255 : r;
	g = (g > 255) ? 255 : g;
	b = (b > 255) ? 255 : b;
	return (ret_color(r, g, b));
}

t_rgb	BRDF_lambertan(t_rgb albedo)
{
	t_rgb	ret;

	ret.r = albedo.r / 255.0 / PI;
	ret.g = albedo.g / 255.0 / PI;
	ret.b = albedo.b / 255.0 / PI;
	return (ret);
}

t_vec	vec_scalar(t_vec a, double b)
{
	t_vec ret;

	ret.x = a.x * b;
	ret.y = a.y * b;
	ret.z = a.z * b;

	return (ret);
}

t_vec	normalize(t_vec v)
{
	double magnitude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

	// Check to avoid division by zero
	if (magnitude == 0) {
		// Return a zero vector or handle this case as needed
		return (t_vec){0, 0, 0}; // or raise an error
	}

	// Divide each component by the magnitude to normalize
	return (t_vec){v.x / magnitude, v.y / magnitude, v.z / magnitude};
}