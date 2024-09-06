/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmandakh <nmandakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:52:43 by nmandakh          #+#    #+#             */
/*   Updated: 2023/11/20 14:14:23 by nmandakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_loop(char *new_string, const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		new_string[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i])
	{
		new_string[j] = s2[i];
		i++;
		j++;
	}
	new_string[j] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size1;
	size_t	size2;
	char	*new_string;

	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	new_string = (char *)malloc((size1 + size2 + 1) * sizeof(char));
	if (new_string == NULL)
	{
		return (NULL);
	}
	ft_loop(new_string, s1, s2);
	return (new_string);
}
/* 
int	main(void)
{
	char	*s1 = "meow";
	char	*s2 = "help";
	char	*new;

	new = ft_strjoin(s1, s2);
	printf("%s", new);
} */