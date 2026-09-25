#include "../../includes/minirt.h"

t_vec3  vect_sub(t_vec3 a, t_vec3 b)
{
    t_vec3 result;

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return (result);
}