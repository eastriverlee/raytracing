#include "vec3.h"
#include "color.h"

int	main()
{
	color pixel_color;
	const int image_width = 256;
	const int image_height = 256;
	int i, j;

	printf("P3\n%d %d\n255\n", image_width, image_height);
	for (j = image_height-1; j >= 0; --j)
	{
		fprintf(stderr, "\rScanlines remaining: %d ", j), fflush(stderr);
		for (i = 0; i < image_width; ++i)
		{
			update(&pixel_color, (double)i/(image_width-1), (double)j/(image_height-1), 0.25);
			write_color(pixel_color);
		}
	}
	fprintf(stderr, "\nDone.\n");
}
