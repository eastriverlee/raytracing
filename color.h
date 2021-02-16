#ifndef COLOR_H
# define COLOR_H

# include "vec3.h"
# include "rtweekend.h"

void write_color(color pixel_color, int samples_per_pixel)
{
	double r = pixel_color.x;
	double g = pixel_color.y;
	double b = pixel_color.z;

	double scale = 1.0 / samples_per_pixel;
	r = sqrt(scale * r);
	g = sqrt(scale * g);
	b = sqrt(scale * b);

	int ir = (int)(256 * clamp(r, 0.0, 0.999));
	int ig = (int)(256 * clamp(g, 0.0, 0.999));
	int ib = (int)(256 * clamp(b, 0.0, 0.999));

	printf("%d %d %d\n", ir, ig, ib);
}

#endif
