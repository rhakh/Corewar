/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 16:43:17 by rhakh             #+#    #+#             */
/*   Updated: 2017/09/24 15:27:31 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LIST_H
# define LINKED_LIST_H

# include <stdlib.h>
# include "ft_printf.h"

typedef struct			s_linked_list
{
	void			*data;
	void			*next;
}						t_linked_list;

t_linked_list			*list_new();
t_linked_list			*list_push_back(t_linked_list **head, void *data);
t_linked_list			*list_append_to_tail(t_linked_list **tail, void *data);
void					list_print(t_linked_list *curr, void (*print)(void *));
void					list_del(t_linked_list **head,
								void (*function_for_del_data)(void *));

#endif
