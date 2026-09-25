#include "../../includes/minirt.h"

t_hit	find_closest_hit(t_app *app, t_ray ray)
{
	t_hit	hit;
	double	t;
    int     i;

	hit.t = -1;
	hit.object = NULL;
    i = 0;
    while (i < app->object_count)
    {
        t = intersect_object(ray, &app->objects[i]);
        if (t > 0 && (hit.t < 0 || t < hit.t))
        {
	        hit.t = t;
	        hit.object = &app->objects[i];
        }
        i++;
    }
	return (hit);
}