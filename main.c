#include "rtweekend.h"

#include "color.h"
#include "material.h"
#include "hittable_list.h"
#include "sphere.h"
#include "moving_sphere.h"
#include "camera.h"

#define make_lambertian(c) material_(lambertian, c, FALSE, FALSE); 
#define make_metal(c, f) material_(metal, c, f, FALSE); 
#define make_dielectric(i) material_(dielectric, color_(1,1,1), FALSE, i); 

list *random_scene()
{
	color albedo;
	list *world = NULL;
	int a, b;

	material ground_material = make_lambertian(color_(0.5, 0.5, 0.5));
	push(&world, list_(sphere_(point3_(0,-1000,0), 1000, ground_material)));

	for (a = -11; a < 11; a++)
		for (b = -11; b < 11; b++)
		{
			double choose_mat = random_double();
			point3 center = point3_(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

			if ((length(subtract(center, point3_(4, 0.2, 0))) > 0.9))
			{
				material sphere_material;

				if (choose_mat < 0.8)
				{
					albedo = multiply__(vec3_random(), vec3_random());
					sphere_material = make_lambertian(albedo);
					point3 center_ = add(center, vec3_(0, random_double_(0,0.5), 0));
					push(&world, list_(moving_sphere_(center, center_, 0.0, 1.0, 0.2, sphere_material)));
				}
				else 
				{
					if (choose_mat < 0.95)
					{
						albedo = vec3_random_(0.5, 1);
						double fuzz = random_double_(0, 0.5);
						sphere_material = make_metal(albedo, fuzz);
						push(&world, list_(sphere_(center, 0.2, sphere_material)));
					}
					else
						sphere_material = make_dielectric(1.5);
					push(&world, list_(sphere_(center, 0.2, sphere_material)));
				}
			}
		}

	material material1 = make_dielectric(1.5);
	push(&world, list_(sphere_(point3_(0, 1, 0), 1, material1)));

	material material2 = make_lambertian(color_(0.4, 0.2, 0.1));
	push(&world, list_(sphere_(point3_(-4, 1, 0), 1, material2)));

	material material3 = make_metal(color_(0.7, 0.6, 0.5), 0);
	push(&world, list_(sphere_(point3_(4, 1, 0), 1, material3)));

	return (world);
}

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
	const float aspect_ratio = 1 / 1;
	const int image_width = 400;
	const int image_height = (int)(image_width / aspect_ratio);
	const int samples_per_pixel = 20;
	const int max_depth = 20;
	int i, j, s;

	list *world = random_scene();

	point3 lookfrom = point3_(13,2,3);
	point3 lookat = point3_(0,0,0);
	vec3 vup = vec3_(0,1,0);
	double dist_to_focus = 10;
	double aperture = 0.1;

	camera cam = camera_(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus, 0, 1);

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
