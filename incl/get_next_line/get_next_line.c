/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmandakh <nmandakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:21:29 by nmandakh          #+#    #+#             */
/*   Updated: 2023/12/16 19:30:10 by nmandakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*gnl_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	else
		return (NULL);
}

char	*fill_line(int fd, char *result, char *buff)
{
	ssize_t	bytes_read;
	char	*temp;

	bytes_read = 1;
	while (0 < bytes_read)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(result);
			return (NULL);
		}
		else if (bytes_read == 0)
			break ;
		buff[bytes_read] = '\0';
		if (!result)
			result = gnl_strdup("");
		temp = result;
		result = gnl_strjoin(temp, buff);
		free(temp);
		temp = NULL;
		if (gnl_strchr(buff, '\n'))
			break ;
	}
	return (result);
}

static char	*set_line(char *buff)
{
	char	*result;
	int		i;

	i = 0;
	while (buff[i] != '\n' && buff[i] != '\0')
		i++;
	if (buff[i] == 0 || buff[1] == 0)
		return (NULL);
	result = gnl_substr(buff, i + 1, gnl_strlen(buff) - i);
	if (result[0] == 0)
	{
		free(result);
		result = NULL;
	}
	buff[i + 1] = 0;
	return (result);
}

char	*get_next_line(int fd)
{
	static char		*remainder;
	char			*buff;
	char			*result;

	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(remainder);
		free(buff);
		remainder = NULL;
		buff = NULL;
		return (NULL);
	}
	result = fill_line(fd, remainder, buff);
	free(buff);
	buff = NULL;
	if (!result)
		return (NULL);
	remainder = set_line(result);
	return (result);
}

// int	main()
// {
// 	int	fd;

// 	fd = open("meow.txt", O_RDONLY);
// 	printf("%s", get_next_line(fd));
// }