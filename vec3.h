#ifndef VEC3_H
# define VEC3_H

# include <math.h>

typedef struct	vec3
{
	double x;
	double y;
	double z;
}				vec3;

vec3 *init(vec3 *v, double e1, double e2, double e3)
{
	*v = malloc(sizeof(vec3));
	v->x = e1;
	v->y = e2;
	v->z = e3;
	return (v);
}

vec3 *negative(vec3 v)
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
	return (sqrt(length_squared(v)));
}

double length_squared(vec3 *v)
{
	return (v->x*v->x + v->y*v->y + v->z*v->z);
}

vec3 *plus(vec3 u, vec3 v)
{
	vec3 *_v;
	
	return (init(_v, u.x + v.x, u.y + v.y, u.z + v.z);
}

vec3 *minus(vec3 u, vec3 v)
{
	vec3 *_v;
	
	return (init(_v, u.x - v.x, u.y - v.y, u.z - v.z);
}

double dot(vec3 u, vec3 v)
{
	return (u.x * v.x
			+u.y * v.y
			+u.z * v.z);
}

void cross(vec3 u, vec3 v)
{
	vec3 *_v;

	return (init(_v,
					u.y * v.z - u.z * v.y,
					u.z * v.x - u.x * v.z,
					u.x * v.y - u.y * v.x));
}

vec3 *duplicate(vec3 v)
{
	vec3 *_v;

	return (init(_v, v.x, v.y, v.z));
}

vec3 unit_vector(vec3 v)
{
	vec3 *_v;

	_v = duplicate(v);
	return (divide(_v, length(_v)));
}

typedef vec3 point3;
typedef vec3 color;

#endif
