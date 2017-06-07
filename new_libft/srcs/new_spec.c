/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_spec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 20:58:38 by rhakh             #+#    #+#             */
/*   Updated: 2017/02/23 20:58:39 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			del_spec(t_spec *specs)
{
	t_spec		*curr;
	t_spec		*tmp;

	curr = specs;
	while (curr != NULL)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp);
	}
}

void			erase_spec(t_spec *sp)
{
	int			i;

	i = -1;
	while (++i < space + 1)
		sp->flags[i] = 0;
	sp->size = 0;
	sp->conversion = 0;
	sp->min_field_w = 0;
	sp->l_count = 0;
	sp->h_count = 0;
	sp->precision = -1;
	sp->alone_char = -1;
	sp->next = NULL;
}

t_spec			*new_spec(void)
{
	t_spec		*new;
	int			i;

	i = -1;
	if ((new = (t_spec *)malloc(sizeof(t_spec))) == NULL)
		return (NULL);
	while (++i < space + 1)
		new->flags[i] = 0;
	new->size = 0;
	new->conversion = 0;
	new->min_field_w = 0;
	new->l_count = 0;
	new->h_count = 0;
	new->precision = -1;
	new->alone_char = -1;
	new->next = NULL;
	return (new);
}
