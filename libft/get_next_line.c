/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:24:40 by asene             #+#    #+#             */
/*   Updated: 2024/12/16 13:07:20 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

static char	*ft_join_and_free(char **s1, char const *s2)
{
	char	*new_str;
	int		i;

	new_str = malloc(sizeof(char) * (ft_strlen(*s1) + ft_strlen(s2) + 1));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while ((*s1)[i])
	{
		new_str[i] = (*s1)[i];
		i++;
	}
	while (*s2)
		new_str[i++] = *(s2++);
	new_str[i] = '\0';
	free(*s1);
	return (new_str);
}

static void	move_buffer(char **buffer, size_t eol_index)
{
	char	*temp;

	temp = *buffer;
	*buffer = ft_strdup(*buffer + eol_index + 1);
	free(temp);
}

static size_t	read_file_to_next_line(int fd, char **buffer)
{
	ssize_t	bytes_read;
	char	read_buffer[BUFFER_SIZE + 1];
	char	*eol;

	eol = ft_strchr(*buffer, '\n');
	bytes_read = 1;
	while (bytes_read > 0 && eol == NULL)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		read_buffer[bytes_read] = '\0';
		if (buffer && *buffer)
			*buffer = ft_join_and_free(buffer, read_buffer);
		else
			*buffer = ft_strdup(read_buffer);
		eol = ft_strchr(*buffer, '\n');
	}
	if (bytes_read == 0)
		eol = *buffer + ft_strlen(*buffer) - 1;
	return (eol - *buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;
	int			eol;

	if (fd < 0 || read(fd, 0, 0) < 0)
	{
		if (buffer)
		{
			free(buffer);
			buffer = NULL;
		}
		return (NULL);
	}
	eol = read_file_to_next_line(fd, &buffer);
	if (eol >= 0)
	{
		line = ft_substr(buffer, 0, eol + 1);
		move_buffer(&buffer, eol);
	}
	else
		return (free(buffer), buffer = NULL, NULL);
	return (line);
}
