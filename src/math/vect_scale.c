#include "../../includes/minirt.h"

t_vec3 vect_scale(t_vec3 vector , double number)
{
    t_vec3 result;

    result.x = vector.x * number;
    result.y = vector.y * number;
    result.z = vector.z * number;
    return (result);
}