#include "main.h"

int			is_error_sub(t_main *main, t_array_string *lex_str, char op)
{
	if (op == (char)0x54)
		return (0);
	print_syntax_error("wrong argument in line", lex_str, main);
	return (1);
}

void		build_args_sub(t_main *main, t_array_string *lex_str, int *args, int i)
{
	args[0] = ft_atoi(lex_str->arr[i] + 1);
	i += 2;
	args[1] = ft_atoi(lex_str->arr[i] + 1);
	i += 2;
	args[2] = ft_atoi(lex_str->arr[i] + 1);
}

void		command_sub(t_main *main, t_array_string *lex_str)
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

	if (ret == 0 || is_error_sub(main, lex_str, op))
		return ;

	build_args_sub(main, lex_str, args, i + 1);
	add_bcode(&main->bcode, new_bcode(5, op, args));
	main->pc += 5;
}
