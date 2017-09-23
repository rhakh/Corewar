/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 15:43:39 by rhakh             #+#    #+#             */
/*   Updated: 2017/09/23 15:43:40 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		calculate_label(t_main *main, char *label_name, int *arg)
{
	t_label_table	*label;

	label = find_label_by_name(main->table, label_name);
	if (label == NULL)
		list_push_back(&main->list, new_put_label(label_name, arg, main->pc));
	else
		return (label->offset - main->pc);
	return (0);
}

int				get_arg(t_main *main, t_array_string *lex_str, int *i, int *arg)
{
	if (is_number(lex_str->arr[*i]))
		return (ft_atoi(lex_str->arr[*i]));
	else if (lex_str->arr[*i][0] == ':')
	{
		*i += 1;
		return (calculate_label(main, lex_str->arr[*i], arg));
	}
	else if (lex_str->arr[*i][0] == '%')
	{
		*i += 1;
		if (is_number(lex_str->arr[*i]))
			return (ft_atoi(lex_str->arr[*i]));
		*i += 1;
		return (calculate_label(main, lex_str->arr[*i], arg));
	}
	return (ft_atoi(lex_str->arr[*i] + 1));
}

void			write_args(int fd, t_bcode *curr)
{
	int			i;

	i = 0;
	while (curr->arg_type[i] != 0)
	{
		if (curr->arg_type[i] == T_DIR)
			(g_tab[*curr->oper_number - 1].dir_as_label) ?
			(write_one_arg(fd, (unsigned int)curr->args[i], 8)) :
			(write_one_arg(fd, (unsigned int)curr->args[i], 24));
		else if (curr->arg_type[i] == T_IND)
			write_one_arg(fd, (unsigned int)curr->args[i], 8);
		else if (curr->arg_type[i] == T_REG)
			write(fd, curr->args + i, 1);
		i++;
	}
}
