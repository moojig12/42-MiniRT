#include "minirt.h"

// Function expects proper input! No '+' allowed
double	ft_atof(char *str)
{
	double	result;
	double	fraction;
	int		has_fraction;
	int		sign;

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
