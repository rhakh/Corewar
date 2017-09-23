/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messenger.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 15:41:51 by rhakh             #+#    #+#             */
/*   Updated: 2017/09/23 15:41:53 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		print_error(char *message, t_array_string *lex_str)
{
	ft_printf("{red}Error:{eoc} {yellow}%s: {eoc}", message);
	print_string(lex_str);
	ft_printf("\n");
}

void		print_syntax_error(char *message,
							t_array_string *lex_str, t_main *main)
{
	ft_printf("{red}Error:{eoc} {yellow}%s: {eoc}", message);
	print_string(lex_str);
	ft_printf("\n");
	main->errors++;
}

void		print_syntax_error_label(char *message,
									char *label_name, t_main *main)
{
	ft_printf("{red}Error:{eoc} {yellow}%s: {eoc} %s", message, label_name);
	ft_printf("\n");
	main->errors++;
}

void		init_create_command(int *i, int **args, char arg_type[3],
								t_array_string *lex_str)
{
	*i = 0;
	if ((*args = (int *)malloc(sizeof(int) * 3)) == NULL)
		return ;
	ft_bzero(arg_type, sizeof(char) * 3);
	ft_bzero(*args, sizeof(int) * 3);
	if (lex_str->i >= 1 && !ft_strcmp(lex_str->arr[1], ":") &&
		!is_command(lex_str->arr[0]))
		*i = 2;
}

void		print_array_string(t_array_string *arr)
{
	int		i;

	i = 0;
	if (arr != NULL)
	{
		ft_printf("Array_string = {\n");
		ft_printf("\tsize = %u\n", arr->size);
		ft_printf("\ti = %d\n", arr->i);
		while (i < arr->i)
		{
			ft_printf("\t[%d] = %s\n", i, arr->arr[i]);
			i++;
		}
		ft_printf("}\n");
	}
	else
		ft_printf("Array_string = NULL\n");
}
