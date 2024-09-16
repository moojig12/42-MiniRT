#include "minirt.h"

int	parse_amb(t_main *main, char *input, int index)
{
	if (index > 2 || index < 1)
		perror("Error\ninvalid input for ambience");
	if (index == 1)
	{
		if (ft_atof(input) >= 0 && ft_atof(input) >= 1)
			main->world.amb->ratio = ft_atof(input);
		else
			perror("Error\nWrong ambience light ratio");
	}
	else if (index == 2)
		pop_color(main->world.amb->color, ft_split(input, ','));
}
