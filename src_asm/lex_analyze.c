/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_analyze.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 15:42:46 by rhakh             #+#    #+#             */
/*   Updated: 2017/09/23 15:42:48 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int					is_comment(char *str)
{
	while (*str <= 32 && *str != 0)
		str++;
	if (*str == '#')
		return (1);
	return (0);
}

t_linked_list		*lex_analyze(t_main *main, t_data *code)
{
	t_linked_list	*lex_strs;
	t_array_string	*return_arr;
	int				i;
	int				ret;

	i = -1;
	lex_strs = NULL;
	while (++i < code->i)
	{
		if (!is_empty_line(code->arr[i]) && !is_comment(code->arr[i]))
		{
			ret = check_bot_params(main->name, main->comment, code->arr[i]);
			(ret == 2) ? (main->name_exist = 1) : 0;
			(ret == 3) ? (main->comm_exist = 1) : 0;
			if (!ret)
			{
				return_arr = split_line(code->arr[i]);
				list_push_back(&lex_strs, return_arr);
			}
		}
	}
	return (lex_strs);
}

void				print_lex(t_linked_list *lex_strs)
{
	t_linked_list	*curr;

	curr = lex_strs;
	while (curr != NULL)
	{
		print_array_string(curr->data);
		curr = curr->next;
	}
}

void				del_lex_strs(t_linked_list *lex_strs)
{
	t_linked_list	*curr;
	t_array_string	*arr;

	curr = lex_strs;
	while (curr != NULL)
	{
		arr = curr->data;
		del_array_string(&arr);
		curr = curr->next;
	}
	list_del(&lex_strs, NULL);
}
