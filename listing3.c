#include <stdio.h>

int	main()
{
	const int image_width = 256;
	const int image_height = 256;
	int i, j;

	printf("P3\n%d %d\n255\n", image_width, image_height);
	for (j = image_height-1; j >= 0; --j)
	{
		fprintf(stderr, "\rScanlines remaining: %d ", j), fflush(stderr);
		for (i = 0; i < image_width; ++i)
		{
			double r = (double)i / (image_width-1);
			double g = (double)j / (image_height-1);
			double b = 0.25;
			int ir = (int)(255.999*r);
			int ig = (int)(255.999*g);
			int ib = (int)(255.999*b);
			printf("%d %d %d\n", ir, ig, ib);
		}
	}
	fprintf(stderr, "\nDone.\n");
}
