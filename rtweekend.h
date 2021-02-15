#ifndef RTWEEKEND_H
# define RTWEEKEND_H

# include <math.h>
# include <stdlib.h>

const double infinity = INFINITY;
const double pi = M_PI;

double degrees_to_radians(double degrees)
{
	return (degrees * pi / 180.0);
}

double random_double()
{
	return (rand() / (RAND_MAX + 1.0));
}

double random_double_(double min, double max)
{
	return (min + (max-min)*random_double());
}

double clamp(double x, double min, double max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

# include "ray.h"
# include "vec3.h"

#endif
