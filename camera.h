#ifndef CAMERA_H
# define CAMERA_H

#include "rtweekend.h"

typedef struct	camera
{
	point3 origin;
	point3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
}				camera;

camera camera_(point3 lookfrom, point3 lookat, vec3 vup, double vfov, double aspect_ratio)
{
	camera c;

	double theta = degrees_to_radians(vfov);
	double h = tan(theta/2);
	double viewport_height = 2.0 * h;
	double viewport_width = aspect_ratio * viewport_height;

	vec3 w = unit_vector(subtract(lookfrom, lookat));
	vec3 u = unit_vector(cross(vup, w));
	vec3 v = cross(w, u);

	c.origin = lookfrom;
	c.horizontal = multiply(u, viewport_width);
	c.vertical = multiply(v, viewport_height);
	c.lower_left_corner = subtract(c.origin, divide(c.horizontal, 2));
		subtract_(&c.lower_left_corner, divide(c.vertical, 2));
		subtract_(&c.lower_left_corner, w);
	return (c);
}

ray get_ray(camera *c, double s, double t)
{
	vec3 direction;

	direction = add(c->lower_left_corner, multiply(c->horizontal, s));
		add_(&direction, multiply(c->vertical, t));
		subtract_(&direction, c->origin);
	return (ray_(c->origin, direction));
}

#endif
