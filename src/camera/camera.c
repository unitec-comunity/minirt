#include "../../includes/minirt.h"

void	init_camera(t_camera *camera)
{
	camera->position = vec3(0, 0, 0);
	camera->orientation = vec3(0, 0, 1);
}

t_ray	camera_ray(t_camera *camera, int x, int y)
{
	double	ndc_x;
	double	ndc_y;
	double	screen_x;
	double	screen_y;
	t_vec3	pixel;
	t_vec3	direction;

	ndc_x = (x + 0.5) / WIDTH;
	ndc_y = (y + 0.5) / HEIGHT;
	screen_x = (2.0 * ndc_x) - 1.0;
	screen_y = 1.0 - (2.0 * ndc_y);
	pixel = vec3(screen_x, screen_y, 1.0);
	direction = vect_sub(pixel, camera->position);
	direction = vect_normalize(direction);
	return (ray_create(camera->position, direction));
}