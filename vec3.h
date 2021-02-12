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

vec3 negative(vec3 v)
{
	return (vec3_(-v.x, -v.y, -v.z));
}

vec3 multiply(vec3 *v, double t, int ismutating)
{
	if (ismutating)
	{
		v->x *= t;
		v->y *= t;
		v->z *= t;
		return (*v);
	}
	return (vec3_(v->x*t, v->y*t, v->z*t));
}

vec3 divide(vec3 *v, double t, int ismutating)
{
	return (multiply(v, 1/t, ismutating));
}

double dot(vec3 u, vec3 v)
{
	return (u.x * v.x
			+u.y * v.y
			+u.z * v.z);
}

double length(vec3 v)
{
	return (sqrt(dot(v, v)));
}

vec3 plus(vec3 u, vec3 v)
{
	return (vec3_(u.x + v.x, u.y + v.y, u.z + v.z));
}

vec3 minus(vec3 u, vec3 v)
{
	return (vec3_(u.x - v.x, u.y - v.y, u.z - v.z));
}

vec3 cross(vec3 u, vec3 v)
{
	return (vec3_(u.y * v.z - u.z * v.y,
					u.z * v.x - u.x * v.z,
					u.x * v.y - u.y * v.x));
}

vec3 unit_vec3_(vec3 v)
{
	return (divide(&v, length(v), FALSE));
}

void update(vec3 *v, double e1, double e2, double e3)
{
	v->x = e1;
	v->y = e2;
	v->z = e3;
}

typedef vec3 point3;
typedef vec3 color;

#endif
