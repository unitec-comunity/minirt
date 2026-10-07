/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parse_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemos <lemos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 00:00:00 by lemos             #+#    #+#             */
/*   Updated: 2026/09/29 00:00:00 by lemos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minirt.h"

static int	tokenize(char *line, char **tokens)
{
	int	count;

	count = 0;
	while (*line)
	{
		while (*line == ' ' || *line == '\t' || *line == '\n'
			|| *line == '\r')
			line++;
		if (!*line)
			break ;
		if (count == 7)
			return (8);
		tokens[count++] = line;
		while (*line && *line != ' ' && *line != '\t' && *line != '\n'
			&& *line != '\r')
			line++;
		if (*line)
			*line++ = '\0';
	}
	return (count);
}

int	scene_parse_line(char *line, int line_no, int *state, t_app *app)
{
	char	*tokens[7];
	int		count;

	count = tokenize(line, tokens);
	if (count && !scene_parse_record(tokens, count, state, app))
	{
		printf("Error\nInvalid scene line %d\n", line_no);
		return (0);
	}
	return (1);
}
