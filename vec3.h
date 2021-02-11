#ifndef VEC3_H
# define VEC3_H

# include <math.h>

typedef struct vec3
{
	double *e[3];
	double x;
	double y;
	double z;
} vec3;

vec3 *init(vec3 *v, double e1, double e2, double e3)
{
	*v = malloc(sizeof(vec3));
	v->x = e1;
	v->y = e2;
	v->z = e3;
	*(v->e[0]) = v->x;
	*(v->e[1]) = v->y;
	*(v->e[2]) = v->z;
	return (v);
}

vec3 *minus(vec3 v)
{
	vec3 *_v;

	return (init(_v, -v.x, -v.y, -v.z));
}

void multiply(vec3 *v, double t)
{
	v->x *= t;
	v->y *= t;
	v->z *= t;
}

void divide(vec3 *v, double t)
{
	multiply(v, 1/t);
}

double length(vec3 *v)
{
	return (sqrt(length_squared(v));
}

double length_squared(vec3 *v)
{
	return (v->x*v->x + v->y*v->y + v->z*v->z);
}

typedef vec3 point3;
typedef vec3 color;

#endif
