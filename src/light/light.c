#include "../../includes/minirt.h"

int	color_from_intensity(double intensity)
{
	int	value;

	value = (int)(255 * intensity);
	return ((value << 16) | (value << 8) | value);
}

double	final_intensity(double ambient, double diffuse)
{
	double	intensity;

	intensity = ambient + diffuse;
	if (intensity > 1.0)
		intensity = 1.0;
	return (intensity);
}

double	diffuse_light(t_vec3 normal, t_vec3 light_dir)
{
	double	intensity;

	intensity = vect_dot(normal, light_dir);
	if (intensity < 0.0)
		intensity = 0.0;
	return (intensity);
}

t_color	color_scale(t_color color, double intensity)
{
	t_color	result;

	result.r = color.r * intensity;
	result.g = color.g * intensity;
	result.b = color.b * intensity;
	return (result);
}

int	color_to_int(t_color color)
{
	int	r;
	int	g;
	int	b;

	r = (int)color.r;
	g = (int)color.g;
	b = (int)color.b;
	return ((r << 16) | (g << 8) | b);
}