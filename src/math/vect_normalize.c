#include "../../includes/minirt.h"

t_vec3	vect_normalize(t_vec3 v)
{
    double  length;

    length = vec3_length(v);
    if (length == 0)
      return (vec3(0, 0, 0));
    return (vec3(v.x / length, v.y / length, v.z / length));  
}