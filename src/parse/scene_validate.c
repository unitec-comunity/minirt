/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_validate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemos <lemos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 00:00:00 by lemos             #+#    #+#             */
/*   Updated: 2026/09/29 00:00:00 by lemos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minirt.h"

static int	read_scene_line(int fd, char *line)
{
	char	c;
	ssize_t	bytes;
	int		len;

	len = 0;
	bytes = 1;
	while (len < 4095 && bytes > 0)
	{
		bytes = read(fd, &c, 1);
		if (bytes < 0)
			return (-1);
		if (bytes > 0 && c != '\n')
			line[len++] = c;
		else
			break ;
	}
	line[len] = '\0';
	if (len == 4095 && c != '\n')
		return (-1);
	if (bytes == 0 && !len)
		return (0);
	return (len + 1);
}

static int	validate_lines(int fd, int *state, t_app *app)
{
	char	line[4096];
	int		line_no;
	int		len;

	state[0] = 0;
	state[1] = 0;
	state[2] = 0;
	state[3] = 0;
	line_no = 0;
	len = read_scene_line(fd, line);
	while (len > 0)
	{
		if (!scene_parse_line(line, ++line_no, state, app))
			return (0);
		len = read_scene_line(fd, line);
	}
	if (len < 0)
	{
		printf("Error\nCould not read scene file or line too long\n");
		return (0);
	}
	return (1);
}

static int	valid_extension(const char *path)
{
	int	len;

	len = 0;
	while (path[len])
		len++;
	return (len >= 3 && scene_string_equal(path + len - 3, ".rt"));
}

int	scene_load(const char *path, t_app *app)
{
	int	state[4];
	int	fd;
	int	valid;

	if (!valid_extension(path))
		return (printf("Error\nScene file must end in .rt\n"), 0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nCould not open scene file\n"), 0);
	app->object_count = 0;
	valid = validate_lines(fd, state, app);
	close(fd);
	if (!valid || !state[0] || !state[1] || !state[2])
		return (printf("Error\nMissing or invalid scene element\n"), 0);
	return (1);
}
