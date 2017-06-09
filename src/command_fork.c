#include "main.h"

int			is_error_fork(t_main *main, t_array_string *lex_str, char op)
{
	if (op == (char)0x80)
		return (0);
	print_syntax_error("wrong argument in line", lex_str, main);
	return (1);
}

void		command_fork(t_main *main, t_array_string *lex_str)
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

	if (ret == 0 || is_error_fork(main, lex_str, op))
		return ;

	args[0] = get_arg(main, lex_str, &i);
	add_bcode(&main->bcode, new_bcode(12, op, args));
	main->pc += 3;
}


//	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},0