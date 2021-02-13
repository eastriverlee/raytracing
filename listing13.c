#include "vec3.h"
#include "ray.h"
#include "color.h"

double hit_sphere(point3 center, double radius, ray r)
{
	vec3 oc = subtract(r.origin, center);
	double a = length_squared(r.direction);
	double half_b = dot(oc, r.direction);
	double c = length_squared(oc) - radius*radius;
	double discriminant = half_b*half_b - a*c;
	if (discriminant < 0)
		return (-1.0);
	else
		return ((-half_b - sqrt(discriminant)) / a);
}

color ray_color(ray r)
{
	double t = hit_sphere(point3_(0,0,-1), 0.5, r);
	if (t > 0.0)
	{
		vec3 N = unit_vector(subtract(at(r, t), vec3_(0,0,-1)));
		return (multiply(color_(N.x+1, N.y+1, N.z+1), 0.5));
	}

	vec3 unit_direction = unit_vector(r.direction);
	t = 0.5*(unit_direction.y + 1.0);
	return (add(multiply(color_(1.0, 1.0, 1.0), 1.0-t), multiply(color_(0.5, 0.7, 1.0), t)));
}

int	main()
{
	const float aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
	const int image_height = (int)(image_width / aspect_ratio);
	int i, j;

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
			color pixel_color = ray_color(r);
			write_color(pixel_color);
		}
	}
	fprintf(stderr, "\nDone.\n");
}
