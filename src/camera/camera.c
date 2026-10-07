#include "../../includes/minirt.h"

void	init_camera(t_camera *camera)
{
	camera->position = vec3(-2.5, 0, 6);
	camera->orientation = vec3(0, 0, 1);
	camera->fov = 70;
}

t_vec3	camera_right(t_vec3 forward)
{
	t_vec3	up;

	up = vec3(0, 1, 0);
	if (fabs(vect_dot(forward, up)) > 0.999)
		up = vec3(0, 0, 1);
	return (vect_normalize(vect_cross(up, forward)));
}

t_vec3	camera_up(t_vec3 forward, t_vec3 right)
{
	return (vect_normalize(vect_cross(forward, right)));
}

t_ray	camera_ray(t_camera *camera, int x, int y)
{
	double	ndc_x;
	double	ndc_y;
	double	screen_x;
	double	screen_y;
	double	aspect;
	double	fov;
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
	t_vec3	direction;

	ndc_x = (x + 0.5) / WIDTH;
	ndc_y = (y + 0.5) / HEIGHT;
	screen_x = 2.0 * ndc_x - 1.0;
	screen_y = 1.0 - 2.0 * ndc_y;
	aspect = (double)WIDTH / HEIGHT;
	fov = camera->fov * M_PI / 180.0;
	forward = vect_normalize(camera->orientation);
	right = camera_right(forward);
	up = camera_up(forward, right);
	direction = forward;
	direction = vect_add(direction,
			vect_scale(right, screen_x * tan(fov / 2.0)));
	direction = vect_add(direction,
			vect_scale(up,
				screen_y * tan(fov / 2.0) / aspect));
	direction = vect_normalize(direction);
	return (ray_create(camera->position, direction));
}