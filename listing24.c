#include "rtweekend.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"

color ray_color(ray r, list **world)
{
	hit_record rec;

	if (hit_(world, r, 0, infinity, &rec))
		return (multiply(add(rec.normal, color_(1,1,1)), 0.5));
	vec3 unit_direction = unit_vector(r.direction);
	double t = 0.5*(unit_direction.y + 1.0);
	return (add(multiply(color_(1.0, 1.0, 1.0), 1.0-t), multiply(color_(0.5, 0.7, 1.0), t)));
}

int	main()
{
	const float aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
	const int image_height = (int)(image_width / aspect_ratio);
	int i, j;

	list *world;
	push(&world, list_(sphere_(point3_(0,0,-1), 0.5)));
	push(&world, list_(sphere_(point3_(0,-100.5,-1), 100)));

	double viewport_height = 2.0;
	double viewport_width = aspect_ratio * viewport_height;
	double focal_length = 1.0;

	point3 origin = point3_(0, 0, 0);
	vec3 horizontal = vec3_(viewport_width, 0, 0);
	vec3 vertical = vec3_(0, viewport_height, 0);
	vec3 lower_left_corner = subtract(origin, divide(horizontal, 2));
		subtract_(&lower_left_corner, divide(vertical, 2));
		subtract_(&lower_left_corner, vec3_(0, 0, focal_length));

	printf("P3\n%d %d\n255\n", image_width, image_height);
	for (j = image_height-1; j >= 0; --j)
	{
		fprintf(stderr, "\rScanlines remaining: %d ", j), fflush(stderr);
		for (i = 0; i < image_width; ++i)
		{
			double u = (double)i / (image_width-1);
			double v = (double)j / (image_height-1);
			vec3 direction = add(lower_left_corner, multiply(horizontal, u));
				add_(&direction, multiply(vertical, v));
			ray r = ray_(origin, direction);
			color pixel_color = ray_color(r, &world);
			write_color(pixel_color);
		}
	}
	clear(&world);
	fprintf(stderr, "\nDone.\n");
}
