#include "main.h"

t_linked_list			*new_linked_list_elem()
{
	t_linked_list		*new;

	new = (t_linked_list *)malloc(sizeof(t_linked_list));
	new->data = NULL;
	new->next = NULL;
	return (new);
}

void			linked_list_push_back(t_linked_list **head, void *data)
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
			curr->next = new_linked_list_elem();
			ptr = curr->next;
			ptr->data = data;
		}
		else
		{
			curr = new_linked_list_elem();
			curr->data = data;
			*head = curr;
		}
	}
}

void			print_linked_list(t_linked_list *curr, void (* function_for_print)(void *))
{
	void		*label;

	while (curr != NULL)
	{
		label = curr->data;
		if (label != NULL)
		{
			function_for_print(label);
			ft_printf("\n");
		}
		curr = curr->next;
	}
}

void			del_linked_list(t_linked_list **head, void (* function_for_del_data)(void *))
{
	t_linked_list	*curr;
	t_linked_list	*next;

	curr = *head;
	if (curr != NULL)
	{
		next = curr;
		while (next != NULL)
		{
			if (curr != NULL)
			{
				next = curr->next;
				function_for_del_data(&curr->data);
				curr->data = NULL;
				curr->next = NULL;
				free(curr);
				curr = next;
			}
		}
		*head = NULL;
	}
}
