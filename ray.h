#ifndef RAY_H
# define RAY_H

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
	return (r.orig + t*r.dir);
}

#endif
