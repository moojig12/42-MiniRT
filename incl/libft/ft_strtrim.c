/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmandakh <nmandakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:13:19 by nmandakh          #+#    #+#             */
/*   Updated: 2023/11/20 14:30:16 by nmandakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_trimloop(char *new_string, int start, int end, const char *s1)
{
	int	i;

	i = 0;
	while (start < end)
	{
		new_string[i] = s1[start];
		start++;
		i++;
	}
	new_string[i] = '\0';
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new_string;
	int		start;
	int		end;

	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	new_string = (char *)malloc((end - start + 1) * sizeof(char));
	if (new_string == NULL)
		return (NULL);
	ft_trimloop(new_string, start, end, s1);
	return (new_string);
}
