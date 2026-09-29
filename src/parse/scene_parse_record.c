/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parse_record.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemos <lemos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 00:00:00 by lemos             #+#    #+#             */
/*   Updated: 2026/09/29 00:00:00 by lemos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minirt.h"

static int	parse_ambient(char **tokens, int count, int *state)
{
	if (count != 3 || state[0])
		return (0);
	if (!parse_scalar_range(tokens[1], 0.0, 1.0, 0)
		|| !parse_vector(tokens[2], 1))
		return (0);
	state[0] = 1;
	return (1);
}

static int	parse_camera(char **tokens, int count, int *state)
{
	if (count != 4 || state[1])
		return (0);
	if (!parse_vector(tokens[1], 0) || !parse_vector(tokens[2], 2)
		|| !parse_scalar_range(tokens[3], 0.0, 180.0, 1))
		return (0);
	state[1] = 1;
	return (1);
}

static int	parse_light(char **tokens, int count, int *state)
{
	if (count != 4 || state[2])
		return (0);
	if (!parse_vector(tokens[1], 0)
		|| !parse_scalar_range(tokens[2], 0.0, 1.0, 0)
		|| !parse_vector(tokens[3], 1))
		return (0);
	state[2] = 1;
	return (1);
}

static int	parse_object(char **t, int n, int *state)
{
	int	valid;

	valid = 0;
	if (scene_string_equal(t[0], "sp") && n == 4)
		valid = parse_vector(t[1], 0) && parse_scalar_range(t[2], 0, 1e12, 1)
			&& parse_vector(t[3], 1);
	else if (scene_string_equal(t[0], "pl") && n == 4)
		valid = parse_vector(t[1], 0) && parse_vector(t[2], 2)
			&& parse_vector(t[3], 1);
	else if (scene_string_equal(t[0], "cy") && n == 6)
		valid = parse_vector(t[1], 0) && parse_vector(t[2], 2)
			&& parse_scalar_range(t[3], 0, 1e12, 1)
			&& parse_scalar_range(t[4], 0, 1e12, 1)
			&& parse_vector(t[5], 1);
	if (!valid || state[3] == MAX_OBJECTS)
		return (0);
	state[3]++;
	return (1);
}

int	scene_parse_record(char **t, int n, int *state)
{
	if (scene_string_equal(t[0], "A"))
		return (parse_ambient(t, n, state));
	if (scene_string_equal(t[0], "C"))
		return (parse_camera(t, n, state));
	if (scene_string_equal(t[0], "L"))
		return (parse_light(t, n, state));
	return (parse_object(t, n, state));
}
