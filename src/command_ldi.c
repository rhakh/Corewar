#include "main.h"

int			is_error_ldi(t_main *main, t_array_string *lex_str, char op)
{
	if (op == (char)0x54 || op == (char)0x94 || op == (char)0xd4 || op == (char)0xe4 || op == (char)0xa4 || op == (char)0x64)
		return (0);
	print_syntax_error("wrong argument in line", lex_str, main);
	return (1);
}

void		inc_pc_ldi(t_main *main, char op)
{
	if (op == (char)0x54)
		main->pc += 5;
	else if (op == (char)0x94 || op == (char)0xd4 || op == (char)0x64)
		main->pc += 6;
	else if (op == (char)0xa4 || op == (char)0xe4)
		main->pc += 7;
}

void		build_args_ldi(t_main *main, t_array_string *lex_str, int *args, int i)
{
	args[0] = get_arg(main, lex_str, &i);
	i += 2;
	args[1] = get_arg(main, lex_str, &i);
	i += 2;
	args[2] = get_arg(main, lex_str, &i);
}

void		command_ldi(t_main *main, t_array_string *lex_str)
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

	if (ret == 0 || is_error_ldi(main, lex_str, op))
		return ;

	build_args_ldi(main, lex_str, args, i + 1);
	add_bcode(&main->bcode, new_bcode(10, op, args));
	inc_pc_ldi(main, op);
}


//{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, "load index", 1, 1},
