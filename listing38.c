#include "rtweekend.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

color ray_color(ray r, list **world, int depth)
{
	hit_record rec;

	if (depth <= 0)
		return (color_(0,0,0));

	if (list_hit(world, r, 0.001, infinity, &rec))
	{
		point3 target = add(rec.p, rec.normal);
			add_(&target, random_unit_vector());
		return (multiply(ray_color(ray_(rec.p, subtract(target, rec.p)), world, depth-1), 0.5));
	}
	vec3 unit_direction = unit_vector(r.direction);
	double t = 0.5*(unit_direction.y + 1.0);
	return (add(multiply(color_(1.0, 1.0, 1.0), 1.0-t), multiply(color_(0.5, 0.7, 1.0), t)));
}

int	main()
{
	const float aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
	const int image_height = (int)(image_width / aspect_ratio);
	const int samples_per_pixel = 100;
	const int max_depth = 50;
	int i, j, s;

	list *world;
	push(&world, list_(sphere_(point3_(0,0,-1), 0.5)));
	push(&world, list_(sphere_(point3_(0,-100.5,-1), 100)));

	camera cam = camera_();

	printf("P3\n%d %d\n255\n", image_width, image_height);
	for (j = image_height-1; j >= 0; --j)
	{
		fprintf(stderr, "\rScanlines remaining: %d ", j), fflush(stderr);
		for (i = 0; i < image_width; ++i)
		{
			color pixel_color = color_(0, 0, 0);
			for (s = 0; s < samples_per_pixel; ++s)
			{
				double u = ((double)i + random_double()) / (image_width-1);
				double v = ((double)j + random_double()) / (image_height-1);
				ray r = get_ray(&cam, u, v);
				add_(&pixel_color, ray_color(r, &world, max_depth));
			}
			write_color(pixel_color, samples_per_pixel);
		}
	}
	clear(&world);
	fprintf(stderr, "\nDone.\n");
}
