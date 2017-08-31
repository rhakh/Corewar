#ifndef LINKED_LIST_H
# define LINKED_LIST_H

# include <stdio.h>
# include <stdlib.h>
# include "ft_printf.h"

typedef struct 			s_linked_list
{
	void 				*data;
	void				*next;
}						t_linked_list;

t_linked_list	*list_new();
t_linked_list	*list_push_back(t_linked_list **head, void *data);
t_linked_list	*list_append_to_tail(t_linked_list **tail, void *data);
void			list_print(t_linked_list *curr, void (* print)(void *));
void			list_del(t_linked_list **head, void (* function_for_del_data)(void *));

#endif
