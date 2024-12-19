/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_bonus2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:37:09 by fjoestin          #+#    #+#             */
/*   Updated: 2024/12/19 17:07:08 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	*ft_free_w(char **result, int w)
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

static int	count_splits(char *str)
{
	int		i;
	int		count;
	bool	ready;

	i = 0;
	count = 0;
	ready = false;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (is_whitespace(str[i]) == false)
			ready = true;
		if (((is_whitespace(str[i]) == true) || str[i + 1] == '\0') 
			&& ready == true)
		{
			ready = false;
			count++;
		}
		i++;
	}
	return (count);
}

static char	*form_word(char *str, int i)
{
	char	*ret;
	int		j;

	j = 0;
	while (str[i + j] != '\0' && (is_whitespace(str[i + j]) == false))
		j++;
	ret = (char *)malloc(sizeof(char) * (j + 1));
	if (!ret)
		return (NULL);
	j = 0;
	while (str[i + j] != '\0' && (is_whitespace(str[i + j]) == false))
	{
		ret[j] = str[i + j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

static char	*make_word(char *str, int pos)
{
	int		i;
	int		count;
	bool	ready;

	i = 0;
	count = 0;
	ready = false;
	while (str[i] != '\0')
	{
		if (is_whitespace(str[i]) == false)
			ready = true;
		if (count == pos && ready == true)
			return (form_word(str, i));
		if ((is_whitespace(str[i]) == true) && ready == true)
		{
			ready = false;
			count++;
		}
		i++;
	}
	return (NULL);
}

char	**split_whitesp(char *str)
{
	char	**ret;
	int		words;
	int		i;

	if (!str)
		return (NULL);
	words = count_splits(str);
	if (words == 0)
		return (NULL);
	ret = (char **)malloc(sizeof(char *) * (words + 1));
	i = 0;
	while (i < words)
	{
		ret[i] = make_word(str, i);
		if (ret[i] == NULL)
		{
			ft_free_w(ret, i);
			return (NULL);
		}
		i++;
	}
	ret[i] = NULL;
	free(str);
	return (ret);
}
