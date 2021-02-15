#ifndef HITTABLE_LIST_H
# define HITTABLE_LIST_H

# include "hittable.h"
# include "list.h"

enum mesh
{
	sphere_;
}

typedef struct	hittable
{
	enum mesh;
	void *pointer;
}				hittable;

void hit(int *hit_anything, double *closest_so_far, hit_record *rec)
{
	hit_record temp_rec;

	*hit_anything = TRUE;
	*closest_so_far = temp_rec.t; 
	*rec = temp_rec;
}

int list_hit(list *lst, ray r, double t_min, double t_max, hit_record *rec)
{
	int hit_anything = FALSE;
	double closest_so_far = t_max;
	void *pointer;

	while ((lst = lst->next))
		switch (lst->content->mesh)
		{
			pointer = lst->content->pointer;
			case sphere_:
			if (sphere_hit(*(sphere *)pointer))
				hit(&hit_anything, &closeset_so_far, &rec);
			break;
		}
	return (hit_anything);
}

#endif
