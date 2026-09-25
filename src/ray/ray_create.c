#include "../../includes/minirt.h"

t_ray	ray_create(t_vec3 origin, t_vec3 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = vect_normalize(direction);
	return (ray);
}