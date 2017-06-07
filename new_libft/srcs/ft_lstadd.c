/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 14:53:48 by rhakh             #+#    #+#             */
/*   Updated: 2016/11/28 14:53:49 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstadd(t_list **alst, t_list *new)
{
	t_list	*tmp;

	tmp = new;
	if (*alst == NULL)
		*alst = tmp;
	else
	{
		tmp->next = *alst;
		*alst = tmp;
	}
	tmp = NULL;
	return ;
}
