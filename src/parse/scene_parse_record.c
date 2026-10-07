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

static int	parse_ambient(char **t, int n, int *s, t_app *app)
{
	double	ratio;

	if (n != 3 || s[0] || !parse_scalar_range(t[1], 0, 1, 0))
		return (0);
	if (!parse_number(t[1], &ratio) || !scene_color(t[2], &app->ambient.color))
		return (0);
	app->ambient.ratio = ratio;
	s[0] = 1;
	return (1);
}

static int	parse_camera(char **t, int n, int *s, t_app *app)
{
	double	fov;

	if (n != 4 || s[1] || !parse_scalar_range(t[3], 0, 180, 1))
		return (0);
	if (!parse_vector(t[1], 0, &app->camera.position)
		|| !parse_vector(t[2], 2, &app->camera.orientation))
		return (0);
	if (!parse_number(t[3], &fov))
		return (0);
	app->camera.fov = fov;
	s[1] = 1;
	return (1);
}

static int	parse_light(char **t, int n, int *s, t_app *app)
{
	double	brightness;

	if (n != 4 || s[2] || !parse_scalar_range(t[2], 0, 1, 0))
		return (0);
	if (!parse_vector(t[1], 0, &app->light.position)
		|| !scene_color(t[3], &app->light.color)
		|| !parse_number(t[2], &brightness))
		return (0);
	app->light.brightness = brightness;
	s[2] = 1;
	return (1);
}

int	scene_parse_record(char **t, int n, int *s, t_app *app)
{
	if (scene_string_equal(t[0], "A"))
		return (parse_ambient(t, n, s, app));
	if (scene_string_equal(t[0], "C"))
		return (parse_camera(t, n, s, app));
	if (scene_string_equal(t[0], "L"))
		return (parse_light(t, n, s, app));
	return (scene_parse_object(t, n, s, app));
}
