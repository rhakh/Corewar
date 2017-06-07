#include "main.h"

void		change_bits(char *op, int nbr, int pair_bit)
{
	if (pair_bit == 1)
	{
		(nbr == REG_CODE) ? (*op = (char)0b01000000 | *op) : 0;
		(nbr == DIR_CODE) ? (*op = (char)0b10000000 | *op) : 0;
		(nbr == IND_CODE) ? (*op = (char)0b11000000 | *op) : 0;
	}
	else if (pair_bit == 2)
	{
		(nbr == REG_CODE) ? (*op = (char)0b00010000 | *op) : 0;
		(nbr == DIR_CODE) ? (*op = (char)0b00100000 | *op) : 0;
		(nbr == IND_CODE) ? (*op = (char)0b00110000 | *op) : 0;
	}
	else if (pair_bit == 3)
	{
		(nbr == REG_CODE) ? (*op = (char)0b00000100 | *op) : 0;
		(nbr == DIR_CODE) ? (*op = (char)0b00001000 | *op) : 0;
		(nbr == IND_CODE) ? (*op = (char)0b00001100 | *op) : 0;
	}
}

int	 		link_or_dir_opc(t_array_string *lex_str, char *op, int *i, int pair_bit)
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
			change_bits(op, DIR_CODE, pair_bit);
		else
		{
			print_error("expect a link in line", lex_str);
			return (0);
		}
	}
	else if (*i < lex_str->i && is_number(lex_str->arr[*i]))
	{
		change_bits(op, DIR_CODE, pair_bit);
	}
	else
	{
		print_error("unknown argument in line", lex_str);
		return (0);
	}
	return (1);
}

int 		get_op_code(t_array_string *lex_str, char *op, int i, int pair_bit)
{
	if (pair_bit > 3 || i >= lex_str->i)
	{
		print_error("too many arguments in line", lex_str);
		return (0);
	}
	if (i < lex_str->i && is_number(lex_str->arr[i]))
		change_bits(op, IND_CODE, pair_bit);
	else
	{
		if (i < lex_str->i && lex_str->arr[i][0] == '%')
		{
			if (link_or_dir_opc(lex_str, op, &i, pair_bit) == 0)
				return (0);
		}
		else if (i < lex_str->i && is_register(lex_str->arr[i]))
			change_bits(op, REG_CODE, pair_bit);
		else if (i < lex_str->i && lex_str->arr[i][0] == ':')
		{
			if (i + 1 < lex_str->i && is_link(lex_str->arr[i + 1]) && i++)
				change_bits(op, IND_CODE, pair_bit);
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
		return (get_op_code(lex_str, op, i + 1, pair_bit + 1));
	else if (i < lex_str->i && lex_str->arr[i][0] != '#')
	{
		print_error("unknown argument in line", lex_str);
		return (0);
	}
	return (1);
}
