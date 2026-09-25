#include "../../includes/minirt.h"

double	intersect_cylinder_side(t_ray ray, t_object *object)
{
	t_vec3	axis;
	t_vec3	oc;
	t_vec3	d_perp;
	t_vec3	oc_perp;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t1;
	double	t2;

	axis = vect_normalize(object->normal);
	oc = vect_sub(ray.origin, object->position);
	d_perp = vect_sub(ray.direction,
			vect_scale(axis, vect_dot(ray.direction, axis)));
	oc_perp = vect_sub(oc,
			vect_scale(axis, vect_dot(oc, axis)));
	a = vect_dot(d_perp, d_perp);
	if (a < 1e-8)
		return (-1);
	b = 2.0 * vect_dot(oc_perp, d_perp);
	c = vect_dot(oc_perp, oc_perp)
		- object->radius * object->radius;
	discriminant = b * b - 4.0 * a * c;
	if (discriminant < 0)
		return (-1);
	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t1 > 0 && cylinder_height_valid(ray, object, t1))
		return (t1);
	if (t2 > 0 && cylinder_height_valid(ray, object, t2))
		return (t2);
	return (-1);
}

double	intersect_cylinder(t_ray ray, t_object *object)
{
	double	side_t;
	double	caps_t;

	side_t = intersect_cylinder_side(ray, object);
	caps_t = intersect_cylinder_caps(ray, object);
	if (side_t > 0 && caps_t > 0)
		return (fmin(side_t, caps_t));
	if (side_t > 0)
		return (side_t);
	if (caps_t > 0)
		return (caps_t);
	return (-1);
}

int	cylinder_height_valid(t_ray ray, t_object *object, double t)
{
	t_vec3	axis;
	t_vec3	point;
	double	height;

	axis = vect_normalize(object->normal);
	point = ray_at(ray, t);
	height = vect_dot(vect_sub(point, object->position), axis);
	if (height >= -object->height / 2.0 && height <= object->height / 2.0)
		return (1);
	return (0);
}