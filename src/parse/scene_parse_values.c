/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parse_values.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemos <lemos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 00:00:00 by lemos             #+#    #+#             */
/*   Updated: 2026/09/29 00:00:00 by lemos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minirt.h"

static int	integer_part(const char **str, double *value)
{
	int	digits;

	digits = 0;
	while (**str >= '0' && **str <= '9')
	{
		*value = *value * 10.0 + (**str - '0');
		(*str)++;
		digits++;
	}
	return (digits);
}

static int	fraction_part(const char **str, double *value)
{
	double	place;
	int		digits;

	place = 0.1;
	digits = 0;
	while (**str >= '0' && **str <= '9')
	{
		*value += (**str - '0') * place;
		place *= 0.1;
		(*str)++;
		digits++;
	}
	return (digits);
}

int	parse_number(const char *str, double *value)
{
	double	number;
	int		sign;
	int		digits;

	number = 0.0;
	sign = 1;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	digits = integer_part(&str, &number);
	if (*str == '.')
	{
		str++;
		digits += fraction_part(&str, &number);
	}
	if (!digits || *str)
		return (0);
	if (!isfinite(number))
		return (0);
	*value = number * sign;
	return (1);
}

static int	vector_part(char **str, int last, double *value, int mode)
{
	int	len;

	len = 0;
	while ((*str)[len] && (*str)[len] != ',')
		len++;
	if (!len || (last && (*str)[len]) || (!last && !(*str)[len]))
		return (0);
	if ((*str)[len] == ',')
		(*str)[len] = '\0';
	if (!parse_number(*str, value))
		return (0);
	if (mode == 1 && (*value < 0 || *value > 255
			|| *value != (int)*value))
		return (0);
	if (mode == 2 && (*value < -1.0 || *value > 1.0))
		return (0);
	*str += len + 1;
	return (1);
}

int	parse_vector(char *str, int mode)
{
	double	value[3];
	int		i;
	double	length;

	i = 0;
	while (i < 3)
	{
		if (!vector_part(&str, i == 2, &value[i], mode))
			return (0);
		i++;
	}
	length = value[0] * value[0] + value[1] * value[1] + value[2] * value[2];
	if (mode == 2 && (length < 0.998 || length > 1.002))
		return (0);
	return (1);
}
