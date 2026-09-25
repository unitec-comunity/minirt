#include "../../includes/minirt.h"

t_vec3	cylinder_normal(t_object *object, t_vec3 point)
{
	t_vec3	axis;
	t_vec3	oc;
	double	height;

	axis = vect_normalize(object->normal);
	oc = vect_sub(point, object->position);
	height = vect_dot(oc, axis);
	if (height >= object->height / 2.0 - 1e-6)
		return (axis);
	if (height <= -object->height / 2.0 + 1e-6)
		return (vect_scale(axis, -1));
	oc = vect_sub(oc, vect_scale(axis, height));
	return (vect_normalize(oc));
}

int	cylinder_cap_valid(t_vec3 point, t_vec3 center, double radius)
{
	t_vec3	diff;

	diff = vect_sub(point, center);
	if (vect_dot(diff, diff) <= radius * radius)
		return (1);
	return (0);
}

double	intersect_cylinder_cap(t_ray ray, t_object *object,
		t_vec3 center, t_vec3 normal)
{
	double	denominator;
	double	t;
	t_vec3	point;

	denominator = vect_dot(ray.direction, normal);
	if (fabs(denominator) < 1e-6)
		return (-1);
	t = vect_dot(vect_sub(center, ray.origin), normal)
		/ denominator;
	if (t <= 0)
		return (-1);
	point = ray_at(ray, t);
	if (cylinder_cap_valid(point, center, object->radius))
		return (t);
	return (-1);
}

double	intersect_cylinder_caps(t_ray ray, t_object *object)
{
	t_vec3	axis;
	t_vec3	top_center;
	t_vec3	bottom_center;
	double	top_t;
	double	bottom_t;

	axis = vect_normalize(object->normal);
	top_center = vect_add(
		object->position,
		vect_scale(axis, object->height / 2.0));
	bottom_center = vect_sub(
		object->position,
		vect_scale(axis, object->height / 2.0));
	top_t = intersect_cylinder_cap(
		ray, object, top_center, axis);
	bottom_t = intersect_cylinder_cap(
		ray, object, bottom_center, axis);
	if (top_t > 0 && bottom_t > 0)
		return (fmin(top_t, bottom_t));
	if (top_t > 0)
		return (top_t);
	if (bottom_t > 0)
		return (bottom_t);
	return (-1);
}