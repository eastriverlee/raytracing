#ifndef HITTABLE_LIST_H
# define HITTABLE_LIST_H

# include "hittable.h"
# include "sphere.h"

typedef struct	list
{
	hittable object;
	struct list *next;
}				list;

list	*list_(hittable object)
{
	list	*new;

	new = malloc(sizeof(list));
	if (new)
	{
		new->object = object;
		new->next = NULL;
	}
	return (new);
}

void	push(list **lst, list *new)
{
	list	*temp;

	temp = *lst;
	*lst = new;
	(*lst)->next = temp;
}

void	drop(list *lst)
{
	if (lst)
	{
		free(lst->object.pointer);
		free(lst);
	}
}

void	clear(list **lst)
{
	list	*temp;

	if (lst)
	{
		while (*lst)
		{
			temp = (*lst)->next;
			drop(*lst);
			(*lst) = temp;
		}
		lst = NULL;
	}
}

static int hit_(hittable *object, ray *r, double t_min, double t_max, hit_record *rec)
{
	int is_hit = FALSE;

	switch (object->geometry)
	{
		case _sphere:
			if (hit_sphere(object->pointer, r, t_min, t_max, rec))
				is_hit = TRUE;
	}
	if (is_hit)
		rec->material = object->material;
	return (is_hit);
}

int hit(list *current, ray *r, double t_min, double t_max, hit_record *rec)
{
	hit_record temp_rec;
	double closest_so_far = t_max;
	int hit_anything = FALSE;

	while (current)
	{
		if (hit_(&current->object, r, t_min, t_max, &temp_rec) && temp_rec.t < closest_so_far)
		{
			hit_anything = TRUE;
			closest_so_far = temp_rec.t; 
			*rec = temp_rec;
		}
		current = current->next;
	}
	return (hit_anything);
}

#endif
