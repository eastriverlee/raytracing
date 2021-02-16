#ifndef VEC3_H
# define VEC3_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define TRUE	1
# define FALSE	0

typedef struct	vec3
{
	double x;
	double y;
	double z;
}				vec3;

vec3 vec3_(double e1, double e2, double e3)
{
	vec3 v;

	v.x = e1;
	v.y = e2;
	v.z = e3;
	return (v);
}

vec3 vec3_random()
{
	return (vec3_(random_double(), random_double(), random_double()));
}

vec3 vec3_random_(double min, double max)
{
	return (vec3_(random_double_(min,max), random_double_(min,max), random_double_(min,max)));
}

void update(vec3 *v, double e1, double e2, double e3)
{
	v->x = e1;
	v->y = e2;
	v->z = e3;
}

vec3 negate(vec3 v)
{
	return (vec3_(-v.x, -v.y, -v.z));
}

void multiply_(vec3 *v, double t)
{
	v->x *= t;
	v->y *= t;
	v->z *= t;
}

vec3 multiply(vec3 v, double t)
{
	return (vec3_(v.x*t, v.y*t, v.z*t));
}

void divide_(vec3 *v, double t)
{
	multiply_(v, 1/t);
}

vec3 divide(vec3 v, double t)
{
	return (multiply(v, 1/t));
}

double length_squared(vec3 v)
{
	return (v.x * v.x
			+v.y * v.y
			+v.z * v.z);
}

double length(vec3 v)
{
	return (sqrt(length_squared(v)));
}

void add_(vec3 *u, vec3 v)
{
	update(u, u->x + v.x, u->y + v.y, u->z + v.z);
}

vec3 add(vec3 u, vec3 v)
{
	return (vec3_(u.x + v.x, u.y + v.y, u.z + v.z));
}

void subtract_(vec3 *u, vec3 v)
{
	update(u, u->x - v.x, u->y - v.y, u->z - v.z);
}

vec3 subtract(vec3 u, vec3 v)
{
	return (vec3_(u.x - v.x, u.y - v.y, u.z - v.z));
}

double dot(vec3 u, vec3 v)
{
	return (u.x * v.x
			+u.y * v.y
			+u.z * v.z);
}

vec3 cross(vec3 u, vec3 v)
{
	return (vec3_(u.y * v.z - u.z * v.y,
				u.z * v.x - u.x * v.z,
				u.x * v.y - u.y * v.x));
}

vec3 unit_vector(vec3 v)
{
	return (divide(v, length(v)));
}

vec3 random_in_unit_sphere()
{
	while (TRUE)
	{
		vec3 p = vec3_random_(-1,1);
		if (length_squared(p) >= 1)
			continue;
		return (p);
	}
}

vec3 (*color_)(double e1, double e2, double e3) = vec3_;
vec3 (*point3_)(double e1, double e2, double e3) = vec3_;

typedef vec3 point3;
typedef vec3 color;

#endif
