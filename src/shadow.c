#include "../includes/minirt.h"

int	is_in_shadow(t_app *app, t_vec3 hit_point, t_vec3 normal)
{
	t_vec3	light_dir;
	double	light_distance;
	t_ray	shadow_ray;
	double	t;
	int		i;

	light_dir = vect_sub(app->light.position, hit_point);
	light_distance = vec3_length(light_dir);
	light_dir = vect_normalize(light_dir);

	shadow_ray.origin = vect_add(hit_point, vect_scale(normal, 0.001));
	shadow_ray.direction = light_dir;

	i = 0;
	while (i < app->object_count)
	{
		t = intersect_object(shadow_ray, &app->objects[i]);
		if (t > 0 && t < light_distance)
			return (1);
		i++;
	}
	return (0);
}