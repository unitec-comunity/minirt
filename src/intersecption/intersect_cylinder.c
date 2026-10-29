/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemos <lemos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 00:00:00 by lemos             #+#    #+#             */
/*   Updated: 2026/10/29 00:00:00 by lemos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minirt.h"

static t_vec3	perpendicular_component(t_vec3 vector, t_vec3 axis)
{
	return (vect_sub(vector, vect_scale(axis, vect_dot(vector, axis))));
}

static double	cylinder_side_roots(t_ray ray, t_object *object,
		t_vec3 d_perp, t_vec3 oc_perp)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	roots[2];

	a = vect_dot(d_perp, d_perp);
	if (a < 1e-8)
		return (-1);
	b = 2.0 * vect_dot(oc_perp, d_perp);
	c = vect_dot(oc_perp, oc_perp)
		- object->radius * object->radius;
	discriminant = b * b - 4.0 * a * c;
	if (discriminant < 0)
		return (-1);
	roots[0] = (-b - sqrt(discriminant)) / (2.0 * a);
	roots[1] = (-b + sqrt(discriminant)) / (2.0 * a);
	if (roots[0] > 0 && cylinder_height_valid(ray, object, roots[0]))
		return (roots[0]);
	if (roots[1] > 0 && cylinder_height_valid(ray, object, roots[1]))
		return (roots[1]);
	return (-1);
}

double	intersect_cylinder_side(t_ray ray, t_object *object)
{
	t_vec3	axis;
	t_vec3	oc;
	t_vec3	d_perp;
	t_vec3	oc_perp;

	axis = vect_normalize(object->normal);
	oc = vect_sub(ray.origin, object->position);
	d_perp = perpendicular_component(ray.direction, axis);
	oc_perp = perpendicular_component(oc, axis);
	return (cylinder_side_roots(ray, object, d_perp, oc_perp));
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
