#include "main.h"

int			is_error_live(t_array_string *lex_str, char op)
{
	if (op == (char)0x80)
		return (0);
	print_error("wrong argument in line", lex_str);
	return (1);
}

void		live_first_arg(t_array_string *lex_str, int *args, char op, int *i, t_label_table *table)
{
	(*i)++;
	if (lex_str->arr[*i][0] == '%')
	{
		if (is_number(lex_str->arr[*i + 1]))
			args[0] = ft_atoi(lex_str->arr[*i + 1]);
		else
		{
			if (find_label_by_name(table, lex_str->arr[*i + 2]) != NULL)
				args[0] = find_label_by_name(table, lex_str->arr[*i + 2])->offset - *(lex_str->glob_pc);
			else
				print_error("unknown label in line ", lex_str);
		}
	}
}

void		command_live(t_array_string *lex_str, t_bcode **bcode, t_label_table *table, int *pc)
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

	if (ret == 0 || is_error_live(lex_str, op))
		return ;

	live_first_arg(lex_str, args, op, &i, table);
	add_bcode(bcode, new_bcode(1, 0, args));
	*pc += 5;
}



//int 		is_error_live(t_array_string *lex_str)
//{
//	int 	i;
//
//	i = 0;
//	if (lex_str->i >= 1 && !ft_strcmp(lex_str->arr[1], ":"))
//		i = 2;
//	if (lex_str->i > 3 + i && lex_str->arr[i + 3][0] != '#')
//	{
//		ft_printf("{red}Error:{eoc} {yellow}wrong argument in line: {eoc}");
//		print_string(lex_str);
//		ft_printf("\n");
//		return (1);
//	}
//	if (lex_str->i < 2 + i || ft_strcmp(lex_str->arr[i + 1], "%"))
//	{
//		ft_printf("{red}Error:{eoc} {yellow}wrong argument in line: {eoc}");
//		print_string(lex_str);
//		ft_printf("\n");
//		return (1);
//	}
//	if (!is_number(lex_str->arr[i + 2]))
//	{
//		ft_printf("{red}Error:{eoc} {yellow}it is not a number in line: {eoc}");
//		print_string(lex_str);
//		ft_printf("\n");
//		return (1);
//	}
//	return (0);
//}
//
//void		command_live(t_array_string *lex_str, t_bcode **bcode, t_label_table *table, int *pc)
//{
//	int 	i;
//	int 	args[3];
//
//    char    op;
//    int     ret;
//
//	i = 0;
//	ft_bzero(args, sizeof(int) * 3);
//	//if (is_error_live(lex_str))
//	//	return;
//	if (lex_str->i >= 1 && !ft_strcmp(lex_str->arr[1], ":"))
//		i = 2;
//
//	op = 0;
//	ret = get_op_code(lex_str, &op, i + 1, 1);
//	print_string(lex_str);
//	ft_printf("ret = %d, OP_CODE = %x\n", ret, op);
//
//	if (ret == 0)
//		return ;
//
//	args[0] = ft_atoi(lex_str->arr[i + 2]);
//	add_bcode(bcode, new_bcode(1, 0, args));
//    *pc += 5;
//}