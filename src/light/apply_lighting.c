/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_lighting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemos <lemos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 00:00:00 by lemos             #+#    #+#             */
/*   Updated: 2026/09/29 00:00:00 by lemos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minirt.h"

static double	clamp_color(double value)
{
	if (value > 255.0)
		return (255.0);
	if (value < 0.0)
		return (0.0);
	return (value);
}

int	apply_lighting(t_color object, t_app *app, double diffuse,
		t_color *result)
{
	double	ambient;
	double	direct;

	ambient = app->ambient.ratio;
	direct = diffuse * app->light.brightness;
	result->r = object.r * (ambient * app->ambient.color.r / 255.0
			+ direct * app->light.color.r / 255.0);
	result->g = object.g * (ambient * app->ambient.color.g / 255.0
			+ direct * app->light.color.g / 255.0);
	result->b = object.b * (ambient * app->ambient.color.b / 255.0
			+ direct * app->light.color.b / 255.0);
	result->r = clamp_color(result->r);
	result->g = clamp_color(result->g);
	result->b = clamp_color(result->b);
	return (1);
}
