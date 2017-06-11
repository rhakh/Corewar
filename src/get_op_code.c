#include "main.h"
#include <stdio.h>

//void		change_bits(char *op, int nbr, int pair_bit)
//{
//	if (pair_bit == 1)
//	{
//		(nbr == REG_CODE) ? (*op = (char)0b01000000 | *op) : 0;
//		(nbr == DIR_CODE) ? (*op = (char)0b10000000 | *op) : 0;
//		(nbr == IND_CODE) ? (*op = (char)0b11000000 | *op) : 0;
//	}
//	else if (pair_bit == 2)
//	{
//		(nbr == REG_CODE) ? (*op = (char)0b00010000 | *op) : 0;
//		(nbr == DIR_CODE) ? (*op = (char)0b00100000 | *op) : 0;
//		(nbr == IND_CODE) ? (*op = (char)0b00110000 | *op) : 0;
//	}
//	else if (pair_bit == 3)
//	{
//		(nbr == REG_CODE) ? (*op = (char)0b00000100 | *op) : 0;
//		(nbr == DIR_CODE) ? (*op = (char)0b00001000 | *op) : 0;
//		(nbr == IND_CODE) ? (*op = (char)0b00001100 | *op) : 0;
//	}
//}
//
//int	 		link_or_dir_opc(t_array_string *lex_str, char *op, int *i, int pair_bit)
//{
//	(*i)++;
//	if (*i >= lex_str->i)
//	{
//		print_error("miss the argument in line", lex_str);
//		return (0);
//	}
//	if (*i < lex_str->i && lex_str->arr[*i][0] == ':')
//	{
//		if (*i < lex_str->i && is_link(lex_str->arr[*i + 1]) && (*i)++)
//			change_bits(op, DIR_CODE, pair_bit);
//		else
//		{
//			print_error("expect a link in line", lex_str);
//			return (0);
//		}
//	}
//	else if (*i < lex_str->i && is_number(lex_str->arr[*i]))
//	{
//		change_bits(op, DIR_CODE, pair_bit);
//	}
//	else
//	{
//		print_error("unknown argument in line", lex_str);
//		return (0);
//	}
//	return (1);
//}

char 		get_op_code(char arg_type[3])
{
	char 	op;
	int 	i;

	i = 0;
	op = 0;
	while (i < 3)
	{
		ft_printf("nbr_REG = %#0hhb\n", (char)0b00000001 << (6 - i * 2));
		ft_printf("nbr_DIR = %#0hhb\n", (char)0b00000010 << (6 - i * 2));
		ft_printf("nbr_IND = %#0hhb\n", (char)0b00000011 << (6 - i * 2));


		(arg_type[i] == T_REG) ? (op = ((char)0b00000001 << (6 - i * 2)) | op) : 0;
		(arg_type[i] == T_DIR) ? (op = ((char)0b00000010 << (6 - i * 2)) | op) : 0;
		(arg_type[i] == T_IND) ? (op = ((char)0b00000011 << (6 - i * 2)) | op) : 0;
		i++;
	}
	return (op);
}
