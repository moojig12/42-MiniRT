/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmandakh <nmandakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 09:55:51 by nmandakh          #+#    #+#             */
/*   Updated: 2023/11/16 14:46:14 by nmandakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*string1;
	const unsigned char	*string2;
	size_t				i;

	string1 = (const unsigned char *)s1;
	string2 = (const unsigned char *)s2;
	i = sizeof(unsigned char);
	if (n == 0)
		return (0);
	while (*string1 == *string2 && i < n)
	{
		string1++;
		string2++;
		i += sizeof(unsigned char);
	}
	return (*string1 - *string2);
}
