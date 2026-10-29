/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_at.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemos <lemos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 00:00:00 by lemos             #+#    #+#             */
/*   Updated: 2026/10/29 00:00:00 by lemos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minirt.h"

t_vec3	ray_at(t_ray ray, double t)
{
	return (vect_add(ray.origin,
			vect_scale(ray.direction, t)));
}

t_vec3	sphere_normal(t_object *object, t_vec3 point)
{
	t_vec3	normal;

	normal = vect_sub(point, object->position);
	return (vect_normalize(normal));
}

t_vec3	object_normal(t_object *object, t_vec3 point)
{
	if (object->type == OBJ_SPHERE)
		return (sphere_normal(object, point));
	else if (object->type == OBJ_PLANE)
		return (vect_normalize(object->normal));
	else if (object->type == OBJ_CYLINDER)
		return (cylinder_normal(object, point));
	return (vec3(0, 0, 0));
}
