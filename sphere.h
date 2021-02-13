#ifndef SPHERE_H
# define SPHERE_H

#include "hittable.h"
#include "vec3.h"

typedef struct	sphere
{
	point3 center;
	double radius;
}				sphere;

int hit_sphere(sphere s, ray r, double t_min, double t_max, hit_record *rec)
{
	vec3 oc = subtract(r.origin, s.center);
	double a = length_squared(r.direction);
	double half_b = dot(oc, r.direction);
	double c = length_squared(oc) - s.radius*s.radius;

	double discriminant = half_b*half_b - a*c;
	if (discriminant < 0)
		return (FALSE);
	double sqrtd = sqrt(discriminant);

	double root = (-half_b - sqrtd) / a;
	if (root < t_min || t_max < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < t_min || t_max < root)
			return (FALSE);
	}

	rec->t = root;
	rec->p = at(r, rec.t);
	rec->normal = divide(subtract(rec.p, center), radius);

	return (TRUE);
}

#endif
