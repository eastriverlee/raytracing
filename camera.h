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

camera camera_()
{
	camera c;

	double aspect_ratio = 16.0 / 9.0;
	double viewport_height = 2.0;
	double viewport_width = aspect_ratio * viewport_height;
	double focal_length = 1.0;

	c.origin = point3_(0, 0, 0);
	c.horizontal = vec3_(viewport_width, 0, 0);
	c.vertical = vec3_(0, viewport_height, 0);
	c.lower_left_corner = subtract(c.origin, divide(c.horizontal, 2));
		subtract_(&c.lower_left_corner, divide(c.vertical, 2));
		subtract_(&c.lower_left_corner, vec3_(0, 0, focal_length));
	return (c);
}

ray get_ray(camera *c, double u, double v)
{
	vec3 direction;

	direction = add(c->lower_left_corner, multiply(c->horizontal, u));
		add_(&direction, multiply(c->vertical, v));
		subtract_(&direction, c->origin);
	return (ray_(c->origin, direction));
}

#endif
