/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parse_object.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemos <lemos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 00:00:00 by lemos             #+#    #+#             */
/*   Updated: 2026/09/29 00:00:00 by lemos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minirt.h"

static int	parse_sphere(char **t, int n, t_object *o)
{
	double	diameter;

	if (n != 4 || !parse_vector(t[1], 0, &o->position)
		|| !parse_scalar_range(t[2], 0, 1e12, 1)
		|| !parse_number(t[2], &diameter)
		|| !scene_color(t[3], &o->color))
		return (0);
	o->type = OBJ_SPHERE;
	o->radius = diameter / 2.0;
	return (1);
}

static int	parse_plane(char **t, int n, t_object *o)
{
	if (n != 4 || !parse_vector(t[1], 0, &o->position)
		|| !parse_vector(t[2], 2, &o->normal)
		|| !scene_color(t[3], &o->color))
		return (0);
	o->type = OBJ_PLANE;
	return (1);
}

static int	parse_cylinder(char **t, int n, t_object *o)
{
	double	diameter;

	if (n != 6 || !parse_vector(t[1], 0, &o->position)
		|| !parse_vector(t[2], 2, &o->normal)
		|| !parse_scalar_range(t[3], 0, 1e12, 1)
		|| !parse_scalar_range(t[4], 0, 1e12, 1)
		|| !parse_number(t[3], &diameter)
		|| !parse_number(t[4], &o->height)
		|| !scene_color(t[5], &o->color))
		return (0);
	o->type = OBJ_CYLINDER;
	o->radius = diameter / 2.0;
	return (1);
}

int	scene_parse_object(char **t, int n, int *state, t_app *app)
{
	t_object	*object;
	int			valid;

	if (state[3] == MAX_OBJECTS)
		return (0);
	object = &app->objects[state[3]];
	object->radius = 0.0;
	object->height = 0.0;
	object->normal = vec3(0.0, 0.0, 0.0);
	valid = 0;
	if (scene_string_equal(t[0], "sp"))
		valid = parse_sphere(t, n, object);
	else if (scene_string_equal(t[0], "pl"))
		valid = parse_plane(t, n, object);
	else if (scene_string_equal(t[0], "cy"))
		valid = parse_cylinder(t, n, object);
	if (!valid)
		return (0);
	state[3]++;
	app->object_count = state[3];
	return (1);
}
