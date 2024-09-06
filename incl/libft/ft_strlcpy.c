/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmandakh <nmandakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:00:23 by nmandakh          #+#    #+#             */
/*   Updated: 2023/11/22 11:53:44 by nmandakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcpy(char *dest, const char *src, size_t d_size)
{
	size_t	len_s;
	size_t	i;

	i = 0;
	len_s = ft_strlen(src);
	if (d_size == 0)
		return (len_s);
	while (d_size - 1 > i && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	if (d_size > 0)
		dest[i] = '\0';
	else if (i > 0)
		dest[i - 1] = '\0';
	return (len_s);
}
/* 
int	main()
{
	char dest[] = "first";
	char src[] = "second";

	printf("%i\n", ft_strlcpy(dest, src, sizeof(dest)));
	printf("result:%s\n", dest);
} */