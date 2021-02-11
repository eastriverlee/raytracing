#ifndef COLOR_H
# define COLOR_H

# include "vec3.h"

void write_color(color pixel_color)
{
	int r = (int)(255.999 * pixel_color.x);
	int g = (int)(255.999 * pixel_color.y);
	int b = (int)(255.999 * pixel_color.z);

	printf("%d %d %d\n", r, g, b);
}

#endif
