#include <stdio.h>

int	main()
{
	const int image_width = 256;
	const int image_height = 256;
	int i, j;

	printf("P3\n%d %d\n255\n", image_width, image_height);
	for (j = image_height-1; j >= 0; --j)
		for (i = 0; i < image_width; ++i)
		{
			double r = (double)i / (double)(image_width-1);
			double g = (double)j / (double)(image_height-1);
			double b = 0.25;
			int ir = (int)(255.999*r);
			int ig = (int)(255.999*g);
			int ib = (int)(255.999*b);
			printf("%d %d %d\n", ir, ig, ib);
		}
}