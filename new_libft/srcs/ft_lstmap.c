/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 15:42:26 by rhakh             #+#    #+#             */
/*   Updated: 2016/11/28 15:42:27 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_list;
	t_list	*curr;

	new_list = NULL;
	if (lst != NULL)
	{
		if ((new_list = f(lst)) == NULL)
			return (NULL);
		curr = new_list;
		while (lst->next != NULL)
		{
			if ((curr->next = f(lst->next)) == NULL)
				return (NULL);
			curr = curr->next;
			lst = lst->next;
		}
	}
	return (new_list);
}
