#ifndef LIST_H
# define LIST_H

# include <stdlib.h>

typedef struct	list
{
	void *content;
	struct list *next;
}				list;

list	*list_(void *content)
{
	list	*new;

	new = malloc(sizeof(list));
	if (new)
	{
		new->content = content;
		new->next = NULL;
	}
	return (new);
}

list	*listlast(list *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

void	listappend(list **lst, list *new)
{
	list	*last;

	if (lst)
	{
		if (!*lst)
			*lst = new;
		else if ((last = listlast(*lst)))
			last->next = new;
	}
}

void	listremove(list *lst, void (*del)(void *))
{
	if (lst)
	{
		del(lst->content);
		free(lst);
	}
}

void	listclear(list **lst, void (*del)(void *))
{
	list	*temp;

	if (lst)
	{
		while (*lst)
		{
			temp = (*lst)->next;
			listremove(*lst, del);
			(*lst) = temp;
		}
		lst = NULL;
	}
}

#endif
