#include "main.h"

t_linked_list			*new_elem()
{
	t_linked_list		*new;

	new = (t_linked_list *)malloc(sizeof(t_linked_list));
	new->data = NULL;
	new->next = NULL;
	return (new);
}

void			list_push_back(t_linked_list **head, void *data)
{
	t_linked_list		*curr;
	t_linked_list		*ptr;

	if (head != NULL)
	{
		curr = *head;
		if (curr != NULL)
		{
			while (curr->next != NULL)
				curr = curr->next;
			curr->next = new_elem();
			ptr = curr->next;
			ptr->data = data;
		}
		else
		{
			curr = new_elem();
			curr->data = data;
			*head = curr;
		}
	}
}

void			print_list_as_put_label(t_linked_list *curr)
{
	t_put_label	*label;

	while (curr != NULL)
	{
		label = curr->data;
		if (label != NULL)
		{
			label->print(label);
			ft_printf("\n");
		}
		curr = curr->next;
	}
}