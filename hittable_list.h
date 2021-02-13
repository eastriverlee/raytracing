#ifndef HITTABLE_LIST_H
# define HITTABLE_LIST_H

# include "hittable.h"
# include "list.h"

int hittable_list_hit(list *lst, ray r, double t_min, double t_max, hit_record *rec)
{
	hit_record temp_rec;
	int hit_anything = FALSE;
	double closest_so_far = t_max;

	while ((lst = lst->next))
		if (sphere_hit(lst->content))
		{
			hit_anything = TRUE;
			closest_so_far = temp_rec.t; 
			rec = temp_rec;
		}
	return (hit_anything);
}

#endif
