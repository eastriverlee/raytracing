#include "rtweekend.h"

#include "color.h"
#include "material.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

color ray_color(ray *r, list *world, int depth)
{
	hit_record rec;

	if (depth <= 0)
		return (color_(0,0,0));

	if (hit(world, r, 0.001, infinity, &rec))
	{
		ray scattered;
		color attenuation;

		if (scatter(r, &rec, &attenuation, &scattered))
			return (multiply__(attenuation, ray_color(&scattered, world, depth-1)));
		return (color_(0,0,0));
	}

	vec3 unit_direction = unit_vector(r->direction);
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

	material material_ground = material_(lambertian, color_(0.8, 0.8, 0.0), FALSE, FALSE);
	material material_center = material_(lambertian, color_(0.1, 0.2, 0.5), FALSE, FALSE);
	material material_left = material_(dielectric, color_(1.0, 1.0, 1.0), FALSE, 1.5);
	material material_right = material_(metal, color_(0.8, 0.6, 0.2), 0.0, FALSE);

	push(&world, list_(sphere_(point3_(0.0,-100.5,-1.0), 100, material_ground)));
	push(&world, list_(sphere_(point3_(0.0,0.0,-1.0), 0.5, material_center)));
	push(&world, list_(sphere_(point3_(-1.0,0.0,-1.0), 0.5, material_left)));
	push(&world, list_(sphere_(point3_(-1.0,0.0,-1.0), -0.4, material_left)));
	push(&world, list_(sphere_(point3_(1.0,0.0,-1.0), 0.5, material_right)));

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
				add_(&pixel_color, ray_color(&r, world, max_depth));
			}
			write_color(pixel_color, samples_per_pixel);
		}
	}
	clear(&world);
	fprintf(stderr, "\nDone.\n");
}
