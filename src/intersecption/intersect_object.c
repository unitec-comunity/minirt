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