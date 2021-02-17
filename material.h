#ifndef MATERIAL_H
# define MATERIAL_H

# include "rtweekend.h"

typedef enum	surface
{
	metal,
	lambertian,
	dielectric
}				surface;

typedef struct	material
{
	color albedo;
	surface surface;
	double fuzz;
	double ir;
}				material;

typedef struct	hit_record
{
	point3 p;
	vec3 normal;
	material material;
	double t;
	int	front_face;
}				hit_record;

material material_(surface s, color c, double f, double ir)
{
	material m;
	m.surface = s;
	m.albedo = c;
	m.fuzz = f;
	m.ir = ir;
	return (m);
}

int scatter(ray *r_in, hit_record *rec, color *attenuation, ray *scattered)
{
	vec3 scatter_direction;
	vec3 reflected;
	vec3 refracted;
	vec3 unit_direction;
	double refraction_ratio;

	switch (rec->material.surface)
	{
		case lambertian:
			scatter_direction = add(rec->normal, random_unit_vector());

			if (near_zero(scatter_direction))
				scatter_direction = rec->normal;
			*scattered = ray_(rec->p, scatter_direction);
			break;
		case metal:
			reflected = reflect(unit_vector(r_in->direction), rec->normal);
			*scattered = ray_(rec->p, add(reflected, multiply(random_in_unit_sphere(), rec->material.fuzz)));
			break;
		case dielectric:
			refraction_ratio = rec->front_face ? (1.0/rec->material.ir) : rec->material.ir;

			unit_direction = unit_vector(r_in->direction);
			refracted = refract(unit_direction, rec->normal, refraction_ratio);
			*scattered = ray_(rec->p, refracted);
	}
	*attenuation = rec->material.albedo;

	return (rec->material.surface != metal || dot(scattered->direction, rec->normal) > 0);
}

#endif
