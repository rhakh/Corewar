/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 14:09:48 by rhakh             #+#    #+#             */
/*   Updated: 2016/11/28 14:09:49 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*next;
	t_list	*curr;

	curr = *alst;
	next = curr->next;
	del(curr->content, curr->content_size);
	curr = next;
	if (alst != NULL)
	{
		while (curr != NULL)
		{
			next = curr->next;
			del(curr->content, curr->content_size);
			free(curr);
			curr = next;
		}
		free(*alst);
		*alst = NULL;
	}
}
