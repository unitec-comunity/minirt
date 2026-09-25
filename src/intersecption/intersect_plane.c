#include "../../includes/minirt.h"

double	intersect_plane(t_ray ray, t_object *object)
{
	double	denominator;
	double	t;
	t_vec3	plane_to_ray;

	denominator = vect_dot(ray.direction, object->normal);
	if (fabs(denominator) < 1e-6)
		return (-1);
	plane_to_ray = vect_sub(object->position, ray.origin);
	t = vect_dot(plane_to_ray, object->normal) / denominator;
	if (t <= 0)
		return (-1);
	return (t);
}