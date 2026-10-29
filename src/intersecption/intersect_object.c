/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemos <lemos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 00:00:00 by lemos             #+#    #+#             */
/*   Updated: 2026/10/29 00:00:00 by lemos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minirt.h"

double	intersect_object(t_ray ray, t_object *object)
{
	if (object->type == OBJ_SPHERE)
		return (intersect_sphere(ray, object));
	else if (object->type == OBJ_PLANE)
		return (intersect_plane(ray, object));
	else if (object->type == OBJ_CYLINDER)
		return (intersect_cylinder(ray, object));
	return (-1);
}
