/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmandakh <nmandakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 09:07:07 by nmandakh          #+#    #+#             */
/*   Updated: 2023/11/21 13:56:25 by nmandakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*string;
	unsigned char	meow;
	size_t			i;

	i = 0;
	string = (unsigned char *)s;
	meow = (unsigned char)c;
	while (i < n)
	{
		if (string[i] == meow)
			return ((void *)&string[i]);
		i += 1;
	}
	return (NULL);
}
/* 
int	main(void)
{
	const char	*str = "Meowhelps";
	const char	chr = 'p';
	const char	*result = (char *)ft_memchr(str, chr, 8);
	
	if (result != NULL)
	{
		printf("%c found at: %ld\n", chr, result - str);
	}
	else
	{
		printf("%c not found\n", chr);
	}
} */