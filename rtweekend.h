#ifndef RTWEEKEND_H
# define RTWEEKEND_H

# include <math.h>

const double infinity = INFINITY;
const double pi = M_PI;

double degrees_to_radians(double degrees)
{
	return (degrees * pi / 180.0);
}

# include "ray.h"
# include "vec3.h"

#endif
