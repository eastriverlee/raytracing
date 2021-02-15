#ifndef CAMERA_H
# define CAMERA_H

#include "rt_weekend.h"

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

	point3 origin = point3_(0, 0, 0);
	vec3 horizontal = vec3_(viewport_width, 0, 0);
	vec3 vertical = vec3_(0, viewport_height, 0);
	vec3 lower_left_corner = subtract(origin, divide(horizontal, 2));
		subtract_(&lower_left_corner, divide(vertical, 2));
		subtract_(&lower_left_corner, vec3_(0, 0, focal_length));

	return (c);
}

get_ray(camera c, double u, double v)
{
	return (ray(origin, c.lower_left_corner, u*c.horizontal + v*c.vertical - c.origin));
}

#endif
