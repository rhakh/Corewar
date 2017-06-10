#include "main.h"

static int	 		link_or_dir_opc(t_array_string *lex_str, char arg_type[3], int *i, int pair_bit)
{
	(*i)++;
	if (*i >= lex_str->i)
	{
		print_error("miss the argument in line", lex_str);
		return (0);
	}
	if (*i < lex_str->i && lex_str->arr[*i][0] == ':')
	{
		if (*i < lex_str->i && is_link(lex_str->arr[*i + 1]) && (*i)++)
			arg_type[pair_bit - 1] = T_DIR;
		else
		{
			print_error("expect a link in line", lex_str);
			return (0);
		}
	}
	else if (*i < lex_str->i && is_number(lex_str->arr[*i]))
		arg_type[pair_bit - 1] = T_DIR;
	else
	{
		print_error("unknown argument in line", lex_str);
		return (0);
	}
	return (1);
}

int				get_args_type(t_array_string *lex_str, char arg_type[3], int i, int pair_bit)
{
	if (pair_bit > 3 || i >= lex_str->i)
	{
		print_error("too many arguments in line", lex_str);
		return (0);
	}
	if (i < lex_str->i && is_number(lex_str->arr[i]))
		arg_type[pair_bit - 1] = T_IND;
	else
	{
		if (i < lex_str->i && lex_str->arr[i][0] == '%')
		{
			if (link_or_dir_opc(lex_str, arg_type, &i, pair_bit) == 0)
				return (0);
		}
		else if (i < lex_str->i && is_register(lex_str->arr[i]))
			arg_type[pair_bit - 1] = T_REG;
		else if (i < lex_str->i && lex_str->arr[i][0] == ':')
		{
			if (i + 1 < lex_str->i && is_link(lex_str->arr[i + 1]) && i++)
				arg_type[pair_bit - 1] = T_IND;
			else
				return (0);
		}
		else
		{
			print_error("unknown argument in line", lex_str);
			return (0);
		}
	}
	if (++i >= lex_str->i)
		return (1);
	if (lex_str->arr[i][0] == ',')
		return (get_args_type(lex_str, arg_type, i + 1, pair_bit + 1));
	else if (i < lex_str->i && lex_str->arr[i][0] != '#')
	{
		print_error("unknown argument in line", lex_str);
		return (0);
	}
	return (1);
}
