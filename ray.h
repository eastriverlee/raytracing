#ifndef RAY_H
# define RAY_H

# include "vec3.h"

typedef struct	ray
{
	point3 orig;
	vec3 dir;
}				ray;

ray ray_(point3 origin, vec3 direction)
{
	ray r;

	r.orig = origin;
	r.dir = direction;
	return (r);
}

point3 at(ray r, double t)
{
	return (add(r.orig, multiply(r.dir, t)));
}

#endif
