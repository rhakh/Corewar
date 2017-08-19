#include "args_functions.h"

/*
** i from 1 to 3 must be
*/
char 		get_arg_type(char opcode, int i)
{
	char	arg_type;

	//		arg_type = (char)((opcode >> (4 - ((i) ? (1 << i) : (0)))) & 0b00000011);
	arg_type = 0;
	if (i == 1)
		arg_type = (char)((opcode >> 6) & 0b00000011);
	else if (i == 2)
		arg_type = (char)((opcode >> 4) & 0b00000011);
	else if (i == 3)
		arg_type = (char)((opcode >> 2) & 0b00000011);
	return (arg_type);
}

int 		get_args(t_data *data, t_bot *bot, char command, char opcode, int args[3])
{
	char 			i;
	char 			arg_type;
	char 			offset;
	unsigned char 	*map;

	i = 0;
	offset = 0;
	map = data->map + bot->pc;
	while (i < op_tab[command - 1].n_arg)
	{
		arg_type = get_arg_type(opcode, i + 1);
		if (arg_type == REG_CODE)
		{
			args[i] = get_number_from_bcode(map + offset, 1);
			if (args[i] > REG_NUMBER || args[i] < 1)
			{
				ft_printf("{red}Wrong number of register{eoc}");
				return (1);
			}
			offset += 1;
		}
		else if (arg_type == DIR_CODE && op_tab[command - 1].dir_as_label)
		{
			args[i] = get_number_from_bcode(map + offset, IND_SIZE);
			offset += IND_SIZE;
		}
		else if (arg_type == DIR_CODE)
		{
			args[i] = get_number_from_bcode(map + offset, DIR_SIZE);
			offset += DIR_SIZE;
		}
		else if (arg_type == IND_CODE)
		{
			args[i] = get_number_from_bcode(map + offset, IND_SIZE);
			offset += IND_SIZE;
		}
		i++;
	}
	return (0);
}