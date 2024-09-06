/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmandakh <nmandakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:19:49 by nmandakh          #+#    #+#             */
/*   Updated: 2023/11/22 12:46:48 by nmandakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*tmp;
	int				i;

	i = 0;
	if (count != 0)
	{
		if (__SIZE_MAX__ / count < size)
			return (NULL);
	}
	tmp = (unsigned char *)malloc(count * size);
	if (tmp == NULL)
		return (NULL);
	while (tmp[i])
	{
		tmp[i] = 0;
		i++;
	}
	return ((void *)tmp);
}
/* 
int main(void)
{
	size_t count;
	size_t size;
	char *test1;
	char *test2;

	count = -5;
	size = -5;
	test1 = calloc(count, size);
	test2 = ft_calloc(count, size);
	printf("calloc: %s\n", test1);
	printf("ft_calloc: %s\n", test2);
} */