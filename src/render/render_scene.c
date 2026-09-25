#include "../../includes/minirt.h"

void	render_scene(t_app *app)
{
	int		x;
	int		y;
	t_ray	ray;
	t_hit	hit;
	t_vec3	hit_point;
	t_vec3	normal;
	t_vec3	light_dir;
	double	intensity;
	int		color;
	double	diffuse;
	t_color	final_color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = camera_ray(&app->camera, x, y);
			hit = find_closest_hit(app, ray);
			if (hit.t > 0)
			{
				hit_point = ray_at(ray, hit.t);
				normal = object_normal(hit.object, hit_point);
				light_dir = vect_normalize(
					vect_sub(app->light.position, hit_point));
				if (is_in_shadow(app, hit_point, normal))
					diffuse = 0.0;
				else
					diffuse = diffuse_light(normal, light_dir);
				intensity = final_intensity(app->ambient.ratio, diffuse);
				final_color = color_scale(hit.object->color, intensity);
				color = color_to_int(final_color);
				img_pixel_put(&app->img, x, y, color);
			}
			else
				img_pixel_put(&app->img, x, y, 0x00000000);
			x++;
		}
		y++;
	}
}