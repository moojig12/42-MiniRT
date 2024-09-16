#include "minirt.h"

double	ft_atof(char *string)
{
	int	i;

	i = 0;
	while (string[i] && string[i] != '.')
	{
		// ?
	}
}

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 12 && c <= 15))
		return (1);
	else
		return (0);
}
