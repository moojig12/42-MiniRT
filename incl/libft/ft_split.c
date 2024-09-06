/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmandakh <nmandakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:49:29 by nmandakh          #+#    #+#             */
/*   Updated: 2023/11/22 12:04:38 by nmandakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>

static int	w_c(const char *s, char lim)
{
	int	booly;
	int	size;

	booly = 0;
	size = 0;
	while (*s)
	{
		if (*s != lim && booly == 0)
		{
			booly = 1;
			size++;
		}
		else if (*s == lim)
			booly = 0;
		s++;
	}
	return (size);
}

static void	ft_init(int *l, int *j, int *w)
{
	*l = 0;
	*j = 0;
	*w = 1;
}

static void	*ft_free(char **result, int w)
{
	int	i;

	i = 0;
	while (i < w)
	{
		free(result[i]);
		result[i] = NULL;
		i++;
	}
	free(result);
	return (NULL);
}

char	**ft_split_str(const char *s, char **result, char d)
{
	int	l;
	int	j;
	int	w;

	ft_init(&l, &j, &w);
	while (s[j])
	{
		if (s[j] != d)
			l++;
		j++;
		if (((s[j] == d && w_c(s, d) > w - 1) || (s[j] == '\0')) && l != 0)
		{
			result[w - 1] = (char *)malloc((l + 1) * sizeof(char));
			if (!(result[w - 1]))
				return (ft_free(result, w - 1));
			ft_strlcpy(result[w - 1], &s[j - l], l + 1);
			w++;
			l = 0;
		}
	}
	result[w - 1] = NULL;
	return (result);
}

char	**ft_split(char const *s, char d)
{
	char	**result;

	result = (char **)malloc((w_c(s, d) + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	result = ft_split_str(s, result, d);
	return (result);
}
/* 
int	main()
{
	char	*string;
	char	limit;
	char	**result;
	int	i;

	string = "bmeowbmeow";
	limit = 'z';
	printf("%i", w_count(string, limit));
	result = ft_split(string, limit);
	if (result == NULL)
		printf("Failed");
	i = 0;
	while (result[i])
	{
		printf("string[%i]:%s\n", i, result[i]);
		i++;
	}
	for (int j = 0; j < 3; j++)
	{
		free(result[j]);
	}
} */