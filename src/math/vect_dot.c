#include "../../includes/minirt.h"

double  vect_dot(t_vec3 a, t_vec3 b)
{
    return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}