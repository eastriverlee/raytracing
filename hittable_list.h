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
	if (lst)
	{
		list	*temp;

		temp = *lst;
		*lst = new;
		(*lst)->next = temp;
	}
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

int hit(hittable *object, ray r, double t_min, double t_max, hit_record *rec)
{
	switch (object->mesh)
	{
		case _sphere:
			if (hit_sphere(object->pointer, r, t_min, t_max, rec))
				return (TRUE);	
			break;
	}
	return (FALSE);
}

int list_hit(list **lst, ray r, double t_min, double t_max, hit_record *rec)
{
	hit_record temp_rec;
	list *current;
	double closest_so_far = t_max;
	int hit_anything = FALSE;

	current = lst ? *lst : NULL;
	while (current)
	{
		if (hit(&(current->object), r, t_min, t_max, &temp_rec))
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
