/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_bonus3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:40:25 by fjoestin          #+#    #+#             */
/*   Updated: 2024/12/17 13:40:51 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (true);
	return (false);
}

bool	is_allwhitespace(char *s)
{
	int		i;
	bool	ret;

	i = 0;
	ret = true;
	while (s[i] && s[i] != '\n')
	{
		if (is_whitespace(s[i]) == false)
			ret = false;
		i++;
	}
	return (ret);
}
