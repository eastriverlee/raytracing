#ifndef MOVING_SPHERE_H
# define MOVING_SPHERE_H

#include "rtweekend.h"
#include "hittable.h"

typedef struct	moving_sphere
{
	point3 center0;
	point3 center1;
	double time0;
	double time1;
	double radius;
}				moving_sphere;

hittable moving_sphere_(point3 cen0, point3 cen1, double time0, double time1, double radius, material material)
{
	hittable h;
	moving_sphere *s;

	h.geometry = _moving_sphere;
	h.material = material;
	h.pointer = malloc(sizeof(moving_sphere));
	if ((s = h.pointer))
	{
		s->center0 = cen0;
		s->center1 = cen1;
		s->time0 = time0;
		s->time1 = time1;
		s->radius = radius;
	}
	return (h);
}

static point3 center(moving_sphere *s, double time)
{
	point3 center;

	center = subtract(s->center1, s->center0);
		multiply_(&center, (time - s->time0) / (s->time1 - s->time0));
		add_(&center, s->center0);
	return (center);
}

int hit_moving_sphere(moving_sphere *s, ray *r, double t_min, double t_max, hit_record *rec)
{
	point3 cen = center(s, r->time);
	vec3 oc = subtract(r->origin, cen);
	double a = length_squared(r->direction);
	double half_b = dot(oc, r->direction);
	double c = length_squared(oc) - s->radius*s->radius;

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
	rec->p = at(r, rec->t);
	vec3 outward_normal = divide(subtract(rec->p, cen), s->radius);
	set_face_normal(rec, r, outward_normal);

	return (TRUE);
}

#endif
