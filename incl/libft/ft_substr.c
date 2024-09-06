/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmandakh <nmandakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:10:47 by nmandakh          #+#    #+#             */
/*   Updated: 2023/11/18 16:12:01 by nmandakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	origin_len;
	char	*result;

	i = 0;
	origin_len = ft_strlen(s);
	if (start > origin_len)
		return (ft_strdup(""));
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
/* 
int	main()
{
	char	*str = "0123456789";
	
	ft_substr(str, 9, 10);
}
 */