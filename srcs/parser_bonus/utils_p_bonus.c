/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_p_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:47:03 by fjoestin          #+#    #+#             */
/*   Updated: 2024/12/17 13:40:41 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int	check_material(char *input)
{
	if (ft_strcmp(input, "metal") == 0)
		return (METAL);
	if (ft_strcmp(input, "glass") == 0)
		return (GLASS);
	if (ft_strcmp(input, "plastic") == 0)
		return (PLASTIC);
	return (STANDARD);
}

void	pop_material_basic(t_material *material)
{
	material->roughness = 0.80;
	material->metalness = 0.13;
}

static char	*get_new_str(char const *s, int start, int end)
{
	int		len;
	char	*str;

	len = end - start;
	if (len < 0)
		len = 0;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	*(str + len) = '\0';
	while (--len >= 0)
		*(str + len) = *(s + start + len);
	return (str);
}

char	*ft_strtrim_mrt(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*chr;
	char	*str;

	start = 0;
	end = ft_strlen(s1);
	chr = ft_strchr(set, *s1);
	while (chr)
	{
		start++;
		chr = ft_strchr(set, *(s1 + start));
	}
	chr = ft_strchr(set, *(s1 + --end));
	while (chr)
	{
		end--;
		chr = ft_strchr(set, *(s1 + end));
	}
	str = get_new_str(s1, start, end + 1);
	return (str);
}
