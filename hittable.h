#ifndef HITTABLE_H
# define HITTABLE_H

# include "ray.h"

typedef struct	hit_record
{
	point3 p;
	vec3 normal;
	double t;
}				hit_record;

#endif
