/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmandakh <nmandakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:34:12 by nmandakh          #+#    #+#             */
/*   Updated: 2023/11/22 12:55:51 by nmandakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;
	size_t		i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	d = (char *)dest;
	s = (const char *)src;
	if (d > s)
		while (0 < n--)
			d[n] = s[n];
	else
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}
/* 
int	main() {
	char	str[] = "Hello, World!";
	char	buffer[20];

	ft_memmove(buffer + 5, str, 10);

	printf("Original string: %s\n", str);
	printf("Copied string: %s\n", buffer + 5);

	return 0;
} */