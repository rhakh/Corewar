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
	while (op_tab[i].name != 0)
	{
		if (name == NULL)
			return (-1);
		if (!ft_strcmp(name, op_tab[i].name))
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
	if (op_tab[n_command].have_opcode)
		main->pc++;
	while (op[i] != 0 && i < 3)
	{
		if (op[i] == T_REG)
			main->pc++;
		if (op[i] == T_IND)
			main->pc += 2;
		if (op[i] == T_DIR && op_tab[n_command].dir_as_label)
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
		if ((op_tab[n_command].type_arg[i] & op[i]) != 0
			|| (op_tab[n_command].type_arg[i] == op[i]))
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
	int		n_command;
	char	arg_type[3];
	int		ret;

	i = 0;
	if ((args = (int *)malloc(sizeof(int) * 3)) == NULL)
		return ;
	ft_bzero(arg_type, sizeof(char) * 3);
	ft_bzero(args, sizeof(int) * 3);
	if (lex_str->i >= 1 && !ft_strcmp(lex_str->arr[1], ":") &&
		!is_command(lex_str->arr[0]))
		i = 2;
	if (i >= lex_str->i)
	{
		free(args);
		return ;
	}
	n_command = find_command_by_name(lex_str->arr[i]);
	ret = get_args_type(lex_str, arg_type, i + 1, 1);
	if (n_command == -1 || ret == 0 || is_error_args(main, lex_str, arg_type, n_command))
	{
		print_syntax_error(" wrong command or arguments", lex_str, main);
		free(args);
		return ;
	}
	build_args(main, lex_str, args, i + 1);
	add_bcode(&main->bcode, new_bcode(op_tab[n_command].command_number, arg_type, args));
	inc_pc(main, arg_type, n_command);
}
