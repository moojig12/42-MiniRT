/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmandakh <nmandakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:01:15 by nmandakh          #+#    #+#             */
/*   Updated: 2023/11/16 15:52:16 by nmandakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *input)
{
	int	i;
	int	positive;
	int	integer;

	i = 0;
	integer = 0;
	positive = 1;
	while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
		i++;
	if (input[i] == '-' || input[i] == '+')
	{
		if (input[i] == '-')
			positive = 0;
		i++;
	}
	while ((input[i] <= 57 && input[i] >= 48))
	{
		integer *= 10;
		integer += input[i] - '0';
		i++;
	}
	if (positive == 0)
		return (-integer);
	return (integer);
}
/* 
int	main()
{
	printf("%i", ft_atoi("2023096690"));
} */