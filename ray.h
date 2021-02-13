#ifndef RAY_H
# define RAY_H

# include "vec3.h"

typedef struct	ray
{
	point3 origin;
	vec3 direction;
}				ray;

ray ray_(point3 origin, vec3 direction)
{
	ray r;

	r.origin = origin;
	r.direction = direction;
	return (r);
}

point3 at(ray r, double t)
{
	return (add(r.origin, multiply(r.direction, t)));
}

#endif
