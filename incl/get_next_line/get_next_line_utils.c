/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmandakh <nmandakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:21:23 by nmandakh          #+#    #+#             */
/*   Updated: 2024/07/09 09:23:07 by nmandakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	origin_len;
	char	*result;

	i = 0;
	origin_len = gnl_strlen(s);
	if (start > origin_len)
		return (gnl_strdup(""));
	else if (len >= origin_len - start)
		len = origin_len - start;
	result = (char *)malloc((len + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	while (i < len && s[i + start])
	{
		result[i] = s[i + start];
		i++;
	}
	result[i] = '\0';
	return (result);
}

static void	gnl_loop(char *new_string, const char *s1, const char *s2)
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

int	gnl_strlen(const char *input)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		i++;
	}
	return (i);
}

char	*gnl_strdup(const char *s)
{
	char	*temp;
	size_t	i;

	temp = (char *)malloc(gnl_strlen(s) + 1);
	i = 0;
	if (temp == NULL)
		return (NULL);
	while (s[i])
	{
		temp[i] = s[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	size_t	size1;
	size_t	size2;
	char	*new_string;

	size1 = gnl_strlen(s1);
	size2 = gnl_strlen(s2);
	new_string = (char *)malloc((size1 + size2 + 1) * sizeof(char));
	if (new_string == NULL)
		return (NULL);
	gnl_loop(new_string, s1, s2);
	return (new_string);
}
