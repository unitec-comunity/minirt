/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtito <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:35:33 by jtito             #+#    #+#             */
/*   Updated: 2025/08/07 12:35:35 by jtito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include	"get_next_line_bonus.h"

static char	*line_get(int fd, char *actual_buffer, char *buffer);
static char	*line_update(char *line);

char	*get_next_line(int fd)
{
	static char	*actual_buffer[MAX_FD];
	char		*line;
	char		*buffer;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
	{
		free(buffer);
		buffer = NULL;
		if (fd >= 0 && fd < MAX_FD && actual_buffer[fd] != NULL)
		{
			free(actual_buffer[fd]);
			actual_buffer[fd] = NULL;
		}
		return (NULL);
	}
	line = line_get(fd, actual_buffer[fd], buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	actual_buffer[fd] = line_update(line);
	return (line);
}

static char	*line_get(int fd, char *actual_buffer, char *buffer)
{
	ssize_t	b_read;
	char	*tmp;

	b_read = 1;
	while (b_read > 0)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read == -1)
		{
			free(actual_buffer);
			return (NULL);
		}
		else if (b_read == 0)
			break ;
		buffer[b_read] = '\0';
		if (!actual_buffer)
			actual_buffer = ft_strdup("");
		tmp = actual_buffer;
		actual_buffer = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (actual_buffer);
}

static char	*line_update(char *line_buffer)
{
	char	*actual_buffer;
	ssize_t	i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == '\0' || line_buffer[i + 1] == '\0')
		return (NULL);
	actual_buffer = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (!actual_buffer || *actual_buffer == '\0')
	{
		free(actual_buffer);
		actual_buffer = NULL;
	}
	line_buffer[i + 1] = 0;
	return (actual_buffer);
}
