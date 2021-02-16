#ifndef HITTABLE_H
# define HITTABLE_H

# include "rtweekend.h"
# include "material.h"

void set_face_normal(hit_record *rec, ray *r, vec3 outward_normal)
{
	rec->front_face = dot(r->direction, outward_normal) < 0;
	rec->normal = rec->front_face ? outward_normal : negate(outward_normal);
}

typedef enum	geometry
{
	_sphere
}				geometry;

typedef struct	hittable
{
	geometry geometry;
	material material;
	void *pointer;
}				hittable;

#endif
