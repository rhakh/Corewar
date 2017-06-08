#include "main.h"


int			is_error_ld(t_main *main, t_array_string *lex_str, char op)
{
	if (op == (char)0xd0 || op == (char)0x90)
		return (0);
	print_syntax_error("wrong argument in line", lex_str, main);
	return (1);
}

int		ld_first_arg(t_main *main, t_array_string *lex_str, int *i)
{
	if (lex_str->arr[*i][0] == '%')//todo load by link
	{
		*i += 1;
		if (is_number(lex_str->arr[*i]))
			return (ft_atoi(lex_str->arr[*i]));
		else
		{
			*i += 1;
			if (find_label_by_name(main->table, lex_str->arr[*i + 1]) != NULL)
				return (find_label_by_name(main->table, lex_str->arr[*i + 1])->offset - main->pc);
			else
				print_syntax_error("unknown label in line ", lex_str, main);
		}
	}
	else if (lex_str->arr[*i][0] == ':')
	{
		*i += 1;
		if (find_label_by_name(main->table, lex_str->arr[*i]) != NULL)
			return (find_label_by_name(main->table, lex_str->arr[*i])->offset - main->pc);
		else
			print_syntax_error("unknown label in line ", lex_str, main);
	}
	else
		return (ft_atoi(lex_str->arr[*i]));
	return (0);
}

void		build_args_ld(t_main *main, t_array_string *lex_str, int *args, int i)
{
	args[0] = ld_first_arg(main, lex_str, &i);
	i += 2;
	args[1] = ft_atoi(lex_str->arr[i] + 1);
}

void		command_ld(t_main *main, t_array_string *lex_str)
{
	int 	i;
	int 	args[3];

	char    op;
	int     ret;

	i = 0;
	ft_bzero(args, sizeof(int) * 3);

	if (lex_str->i >= 1 && !ft_strcmp(lex_str->arr[1], ":") && !is_command(lex_str->arr[0]))
		i = 2;

	op = 0;
	ret = get_op_code(lex_str, &op, i + 1, 1);
	print_string(lex_str);
	ft_printf("ret = %d, OP_CODE = %x\n", ret, op);

	if (ret == 0 || is_error_ld(main, lex_str, op))
		return ;

	build_args_ld(main, lex_str, args, i + 1);
	add_bcode(&main->bcode, new_bcode(2, op, args));
	(op == (char)0x90) ? (main->pc += 7) : (main->pc += 5);
}