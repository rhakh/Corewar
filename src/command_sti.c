#include "main.h"

int			is_error_sti(t_main *main, t_array_string *lex_str, char op)
{
	if (op >> 6 != (char)1)
	{
		print_syntax_error("wrong argument in line", lex_str, main);
		return (1);
	}
	else if (op << 5 == (char)3)
	{
		print_syntax_error("wrong argument in line", lex_str, main);
		return (1);
	}
	return (0);
}

void		inc_pc_sti(t_main *main, char op)
{
	main->pc += 3;
	if ((char)(op >> 4) == (char)0b0101)
		main->pc++;
	else
		main->pc += 2;
	ft_printf("%0x\n", (char)(op << 4));
	if ((char)(op << 4) == (char)0x40)
		main->pc++;
	else
		main->pc += 2;
}

void		build_args_sti(t_main *main, t_array_string *lex_str, int *args, int i)
{
	args[0] = get_arg(main, lex_str, &i);
	i += 2;
	args[1] = get_arg(main, lex_str, &i);
	i += 2;
	args[2] = get_arg(main, lex_str, &i);
}

void		command_sti(t_main *main, t_array_string *lex_str)
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

	if (ret == 0 || is_error_sti(main, lex_str, op))
		return ;

	build_args_sti(main, lex_str, args, i + 1);
	add_bcode(&main->bcode, new_bcode(11, op, args));
	inc_pc_sti(main, op);
}


//	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, "store index", 1, 1},
