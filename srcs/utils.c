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

// returns 1 if within range. 0 if outside of range
int	ft_range_f(double num, double min, double max)
{
	if (num >= min || num <= max)
		return (1);
	else
		return (0);
}

int	print_vec(char *string, t_vec vec)
{
	if (string)
		printf("\n---\n%s\nx: %f\ny: %f\nz: %f\n", string, vec.x, vec.y, vec.z);
	else
		printf("---\nx: %f\ny: %f\nz: %f\n", vec.x, vec.y, vec.z);
	return (0);
}

int	print_color(char *string, t_rgb color)
{
	if (string)
		printf("\n---\n%s\nr: %f\ng: %f\nb: %f\n", string, color.r, color.g, color.b);
	else
		printf("---\nr: %f\ng: %f\nb: %f\n", color.r, color.g, color.b);
	return (0);
}