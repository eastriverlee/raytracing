#ifndef CAMERA_H
# define CAMERA_H

#include "rtweekend.h"

typedef struct	camera
{
	point3 origin;
	point3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 w, u, v;
	double lens_radius;
	double time0, time1;
}				camera;

camera camera_(point3 lookfrom, point3 lookat, vec3 vup, double vfov, double aspect_ratio, double aperture, double focus_dist, double time0, double time1)
{
	camera c;

	double theta = degrees_to_radians(vfov);
	double h = tan(theta/2);
	double viewport_height = 2.0 * h;
	double viewport_width = aspect_ratio * viewport_height;

	c.w = unit_vector(subtract(lookfrom, lookat));
	c.u = unit_vector(cross(vup, c.w));
	c.v = cross(c.w, c.u);

	c.origin = lookfrom;
	c.horizontal = multiply(c.u, viewport_width);
		multiply_(&c.horizontal, focus_dist);
	c.vertical = multiply(c.v, viewport_height);
		multiply_(&c.vertical, focus_dist);
	c.lower_left_corner = subtract(c.origin, divide(c.horizontal, 2));
		subtract_(&c.lower_left_corner, divide(c.vertical, 2));
		subtract_(&c.lower_left_corner, multiply(c.w, focus_dist));

	c.lens_radius = aperture / 2;
	c.time0 = time0;
	c.time1 = time1;
	return (c);
}

ray get_ray(camera *c, double s, double t)
{
	vec3 direction;
	vec3 rd;
	vec3 offset;

	rd = multiply(random_in_unit_disk(), c->lens_radius);
	offset = multiply(c->u, rd.x);
		add_(&offset, multiply(c->v, rd.y));

	direction = add(c->lower_left_corner, multiply(c->horizontal, s));
		add_(&direction, multiply(c->vertical, t));
		subtract_(&direction, c->origin);
		subtract_(&direction, offset);
	return (ray_(add(c->origin, offset), direction, random_double_(c->time0, c->time1)));
}

#endif
