/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parse_range.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemos <lemos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 00:00:00 by lemos             #+#    #+#             */
/*   Updated: 2026/09/29 00:00:00 by lemos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minirt.h"

int	scene_string_equal(const char *left, const char *right)
{
	while (*left && *left == *right)
	{
		left++;
		right++;
	}
	return (*left == *right);
}

int	parse_scalar_range(char *str, double min, double max, int exclusive)
{
	double	value;

	if (!parse_number(str, &value) || value > max)
		return (0);
	if ((exclusive && value <= min) || (!exclusive && value < min))
		return (0);
	return (1);
}
