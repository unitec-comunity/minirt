/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemos <lemos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 00:00:00 by lemos             #+#    #+#             */
/*   Updated: 2026/10/29 00:00:00 by lemos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minirt.h"

static double	pixel_diffuse(t_app *app, t_vec3 point, t_vec3 normal)
{
	t_vec3	light_dir;

	if (is_in_shadow(app, point, normal))
		return (0.0);
	light_dir = vect_normalize(vect_sub(app->light.position, point));
	return (diffuse_light(normal, light_dir));
}

static void	render_pixel(t_app *app, int x, int y)
{
	t_ray	ray;
	t_hit	hit;
	t_vec3	vectors[2];
	double	diffuse;
	t_color	final_color;

	ray = camera_ray(&app->camera, x, y);
	hit = find_closest_hit(app, ray);
	if (hit.t <= 0)
		return (img_pixel_put(&app->img, x, y, 0x00000000));
	vectors[0] = ray_at(ray, hit.t);
	vectors[1] = object_normal(hit.object, vectors[0]);
	diffuse = pixel_diffuse(app, vectors[0], vectors[1]);
	apply_lighting(hit.object->color, app, diffuse, &final_color);
	img_pixel_put(&app->img, x, y, color_to_int(final_color));
}

void	render_scene(t_app *app)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			render_pixel(app, x, y);
			x++;
		}
		y++;
	}
}
