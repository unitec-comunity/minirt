/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemos <lemos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 00:00:00 by lemos             #+#    #+#             */
/*   Updated: 2026/09/29 00:00:00 by lemos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minirt.h"

static void	camera_basis(t_vec3 orientation, t_vec3 *basis);

void	init_camera(t_camera *camera)
{
	camera->position = vec3(0, 0, 0);
	camera->orientation = vec3(0, 0, 1);
	camera->fov = 70.0;
}

static void	camera_basis(t_vec3 orientation, t_vec3 *basis)
{
	t_vec3	world_up;

	basis[0] = vect_normalize(orientation);
	world_up = vec3(0, 1, 0);
	if (fabs(vect_dot(basis[0], world_up)) > 0.999)
		world_up = vec3(0, 0, 1);
	basis[1] = vect_normalize(vect_cross(world_up, basis[0]));
	basis[2] = vect_cross(basis[0], basis[1]);
}

t_ray	camera_ray(t_camera *camera, int x, int y)
{
	double	screen_x;
	double	screen_y;
	double	half_fov;
	t_vec3	basis[3];
	t_vec3	direction;

	screen_x = 2.0 * (x + 0.5) / WIDTH - 1.0;
	screen_y = 1.0 - 2.0 * (y + 0.5) / HEIGHT;
	half_fov = tan(camera->fov * 0.008726646259971648);
	camera_basis(camera->orientation, basis);
	direction = vect_add(basis[0], vect_scale(basis[1], screen_x * half_fov));
	direction = vect_add(direction, vect_scale(basis[2],
				screen_y * half_fov * HEIGHT / WIDTH));
	return (ray_create(camera->position, vect_normalize(direction)));
}
