#include "../../includes/minirt.h"

double	vec3_length(t_vec3 v)
{
	return (sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
}
