/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 16:43:25 by rhakh             #+#    #+#             */
/*   Updated: 2017/09/23 16:43:27 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

t_linked_list			*list_new(void)
{
	t_linked_list		*new;

	new = (t_linked_list *)malloc(sizeof(t_linked_list));
	new->data = NULL;
	new->next = NULL;
	return (new);
}

t_linked_list			*list_push_back(t_linked_list **head, void *data)
{
	t_linked_list		*curr;

	if (head != NULL)
	{
		curr = *head;
		if (curr != NULL)
		{
			while (curr->next != NULL)
				curr = curr->next;
			curr->next = list_new();
			curr = curr->next;
			curr->data = data;
		}
		else
		{
			curr = list_new();
			curr->data = data;
			*head = curr;
		}
		return (curr);
	}
	return (NULL);
}

t_linked_list			*list_append_to_tail(t_linked_list **tail, void *data)
{
	t_linked_list		*node;

	if (tail)
	{
		node = *tail;
		if (node)
		{
			if (node->next)
			{
				ft_printf("{red}Node isn't end of list\n{eoc}");
				return (NULL);
			}
			node->next = list_new();
			node = node->next;
			node->data = data;
		}
		else
		{
			node = list_new();
			node->data = data;
			*tail = node;
		}
		return (node);
	}
	return (NULL);
}

void					list_print(t_linked_list *curr,
						void (*function_for_print)(void *))
{
	void				*label;

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

void					list_del(t_linked_list **head,
						void (*function_for_del_data)(void *))
{
	t_linked_list		*curr;
	t_linked_list		*next;

	if (head != NULL)
		curr = *head;
	else
		return ;
	if (curr != NULL)
	{
		next = curr;
		while (next != NULL)
		{
			if (curr != NULL)
			{
				next = curr->next;
				if (function_for_del_data)
					function_for_del_data(&(curr->data));
				curr->data = NULL;
				curr->next = NULL;
				free(curr);
				curr = next;
			}
		}
		*head = NULL;
	}
}
