/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmandakh <nmandakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:40:41 by nmandakh          #+#    #+#             */
/*   Updated: 2023/11/20 15:52:17 by nmandakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countdigit(long int n)
{
	int	count;

	count = 0;
	if (n == 0)
	{
		count++;
		return (count);
	}
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static long int	ft_negative(long int n, int *neg)
{
	*neg = 0;
	if (n < 0)
	{
		*neg = 1;
		n = -n;
	}
	return (n);
}

char	*ft_itoa(int nbr)
{
	int			neg;
	char		*string;
	int			digit;
	int			len;
	long int	n;

	n = (long int)nbr;
	digit = ft_countdigit(n);
	len = digit;
	n = ft_negative(n, &neg);
	string = (char *)malloc((digit + neg + 1) * sizeof(char));
	if (string == NULL)
		return (NULL);
	if (n == 0)
		string[0] = '0';
	while (0 != digit-- && n != 0)
	{
		string[digit + neg] = ((n % 10) + 48);
		n /= 10;
	}
	if (neg != 0)
		string[0] = '-';
	string[len + neg] = '\0';
	return (string);
}
/* 
int	main()
{
	int	src;
	char	*dest;

	src = 0;
	dest = ft_itoa(src);
	printf("%s", dest);
} */