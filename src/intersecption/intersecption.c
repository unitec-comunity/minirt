#include "../../includes/minirt.h"

double	intersect_sphere(t_ray ray, t_object *object)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t1;
	double	t2;

	oc = vect_sub(ray.origin, object->position);

	a = vect_dot(ray.direction, ray.direction);
	b = 2.0 * vect_dot(ray.direction, oc);
	c = vect_dot(oc, oc)
		- object->radius * object->radius;

	discriminant = b * b - 4.0 * a * c;
	if (discriminant < 0)
		return (-1);

	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);

	if (t1 > 0)
		return (t1);
	if (t2 > 0)
		return (t2);
	return (-1);
}