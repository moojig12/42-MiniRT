/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmandakh <nmandakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:20:01 by nmandakh          #+#    #+#             */
/*   Updated: 2023/11/17 13:44:05 by nmandakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	while (i != -1)
	{
		if (s[i] == (char)c)
		{
			while (i != 0)
			{
				i--;
				s++;
			}
			return ((char *)s);
		}
		i--;
	}
	if (*s == (char)c)
		return ((char *)s);
	else
		return (NULL);
}
/* 
int	main()
{
	const char *s = "omewo";
	char *r = ft_strrchr(s, 111);
	r++;
} */