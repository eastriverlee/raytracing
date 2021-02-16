#ifndef MATERIAL_H
# define MATERIAL_H

# include "rtweekend.h"

typedef enum	surface
{
	metal,
	lambertian
}				surface;

typedef struct	material
{
	color albedo;
	surface surface;
	double fuzz;
}				material;

typedef struct	hit_record
{
	point3 p;
	vec3 normal;
	material material;
	double t;
	int	front_face;
}				hit_record;

material material_(surface s, color c, double f)
{
	material m;
	m.surface = s;
	m.albedo = c;
	m.fuzz = f;
	return (m);
}

int scatter(ray *r_in, hit_record *rec, color *attenuation, ray *scattered)
{
	vec3 scatter_direction;

	switch (rec->material.surface)
	{
		case lambertian:
			scatter_direction = add(rec->normal, random_unit_vector());

			if (near_zero(scatter_direction))
				scatter_direction = rec->normal;
			*scattered = ray_(rec->p, scatter_direction);
			break;
		case metal:
			scatter_direction = reflect(unit_vector(r_in->direction), rec->normal);
			*scattered = ray_(rec->p, add(scatter_direction, multiply(random_in_unit_sphere(), rec->material.fuzz)));
			break;
	}
	*attenuation = rec->material.albedo;

	return (rec->material.surface != metal || dot(scattered->direction, rec->normal) > 0);
}

#endif
