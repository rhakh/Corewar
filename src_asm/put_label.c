/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_label.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 15:43:50 by rhakh             #+#    #+#             */
/*   Updated: 2017/09/23 15:43:51 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			del_put_label(t_put_label **put_label)
{
	if (*put_label != NULL)
	{
		free((*put_label)->name);
		free(*put_label);
		put_label = NULL;
	}
}

void			print_put_label(t_put_label *label)
{
	ft_printf("label_name = %s, &arg = %p, *arg = %d, curr_pc = %d",
			label->name, label->arg, *label->arg, label->curr_pc);
}

t_put_label		*new_put_label(char *name_label, int *arg, int curr_pc)
{
	t_put_label	*new;

	if ((new = (t_put_label *)malloc(sizeof(t_put_label))) == NULL)
		return (NULL);
	new->name = ft_strdup(name_label);
	new->arg = arg;
	new->print_put_label = &print_put_label;
	new->del_put_label = &del_put_label;
	new->curr_pc = curr_pc;
	return (new);
}
