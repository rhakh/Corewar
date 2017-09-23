/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 15:42:33 by rhakh             #+#    #+#             */
/*   Updated: 2017/09/23 15:42:33 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		build_args(t_main *main, t_array_string *lex_str,
						int *args, int i)
{
	args[0] = get_arg(main, lex_str, &i, args + 0);
	i += 2;
	if (i < lex_str->i)
		args[1] = get_arg(main, lex_str, &i, args + 1);
	i += 2;
	if (i < lex_str->i)
		args[2] = get_arg(main, lex_str, &i, args + 2);
}

static int		find_command_by_name(char *name)
{
	int		i;

	i = 0;
	while (g_tab[i].name != 0)
	{
		if (name == NULL)
			return (-1);
		if (!ft_strcmp(name, g_tab[i].name))
			return (i);
		i++;
	}
	return (-1);
}

static void		inc_pc(t_main *main, char op[3], int n_command)
{
	int		i;

	i = 0;
	main->pc++;
	if (g_tab[n_command].have_opcode)
		main->pc++;
	while (op[i] != 0 && i < 3)
	{
		if (op[i] == T_REG)
			main->pc++;
		if (op[i] == T_IND)
			main->pc += 2;
		if (op[i] == T_DIR && g_tab[n_command].dir_as_label)
			main->pc += 2;
		else if (op[i] == T_DIR)
			main->pc += 4;
		i++;
	}
}

static int		is_error_args(t_main *main,
							t_array_string *lex_str, char op[3], int n_command)
{
	int		i;

	if (n_command == -1)
	{
		print_syntax_error(" unknown command in line ", lex_str, main);
		return (1);
	}
	i = 0;
	while (i < 3)
	{
		if ((g_tab[n_command].type_arg[i] & op[i]) != 0
			|| (g_tab[n_command].type_arg[i] == op[i]))
			i++;
		else
		{
			print_syntax_error("wrong argument in line", lex_str, main);
			return (1);
		}
	}
	return (0);
}

void			create_command(t_main *main, t_array_string *lex_str)
{
	int		i;
	int		*args;
	int		n_c;
	char	arg_type[3];
	int		ret;

	args = NULL;
	init_create_command(&i, &args, arg_type, lex_str);
	if (i >= lex_str->i)
	{
		free(args);
		return ;
	}
	n_c = find_command_by_name(lex_str->arr[i]);
	ret = get_args_type(lex_str, arg_type, i + 1, 1);
	if (n_c == -1 || ret == 0 || is_error_args(main, lex_str, arg_type, n_c))
	{
		print_syntax_error(" wrong command or arguments", lex_str, main);
		free(args);
		return ;
	}
	build_args(main, lex_str, args, i + 1);
	add_bcode(&main->bcode, new_bcode(g_tab[n_c].command_number,
									arg_type, args));
	inc_pc(main, arg_type, n_c);
}
