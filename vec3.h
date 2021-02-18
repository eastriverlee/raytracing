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

int near_zero(vec3 v)
{
	double s = 1e-8;
	return ((fabs(v.x) < s) && (fabs(v.y) < s) && (fabs(v.z) < s));
}

vec3 multiply__(vec3 v, vec3 u)
{
	return (vec3_(v.x*u.x, v.y*u.y, v.z*u.z));
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

vec3 random_unit_vector()
{
	return (unit_vector(random_in_unit_sphere()));
}

//vec3 random_in_hemisphere(vec3 normal)
//{
//	vec3 in_unit_sphere = random_in_unit_sphere();
//	if (dot(in_unit_sphere, normal) > 0.0)
//		return (in_unit_sphere);
//	else
//		return (negate(in_unit_sphere));
//}

vec3 random_in_unit_disk()
{
	while (TRUE)
	{
		vec3 p = vec3_(random_double_(-1,1), random_double_(-1,1), 0);
		if (length_squared(p) >= 1)
			continue;
		return (p);
	}
}

vec3 reflect(vec3 v, vec3 n)
{
	return (subtract(v, multiply(n, 2*dot(v,n))));
}

vec3 refract(vec3 uv, vec3 n, double etai_over_etat)
{
	double cos_theta = fmin(dot(negate(uv), n), 1.0);
	vec3 r_out_perp = multiply(add(uv, multiply(n, cos_theta)), etai_over_etat);
	vec3 r_out_parallel = multiply(n, -sqrt(fabs(1.0 - length_squared(r_out_perp))));
	return (add(r_out_perp, r_out_parallel));
}

vec3 (*color_)(double e1, double e2, double e3) = vec3_;
vec3 (*point3_)(double e1, double e2, double e3) = vec3_;

typedef vec3 point3;
typedef vec3 color;

#endif
