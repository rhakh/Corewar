#include "args_functions.h"

/*
** i from 1 to 3 must be, -1 - error
*/

char		get_arg_type(char command, char opcode, int i)
{
	char	arg_type;

	arg_type = (char)((opcode >> (6 - (2 * (i - 1)))) & (0b00000011));
	if (command == 1)
		arg_type = DIR_CODE;
	else if (command == 9 || command == 12 || command == 15)
		arg_type = IND_CODE;
	if (arg_type != DIR_CODE && arg_type != IND_CODE && arg_type != REG_CODE)
		return (-1);
	return (arg_type);
}

int			check_opcode(char command, char opcode)
{
	unsigned char	byte_pair;
	int				i;

	i = 0;
	while (i < op_tab[command - 1].n_arg)
	{
		byte_pair = (unsigned char)((opcode >> (6 - (2 * i))) & 0b00000011);
		(byte_pair == REG_CODE) ? (byte_pair = T_REG) : 0;
		(byte_pair == DIR_CODE) ? (byte_pair = T_DIR) : 0;
		(byte_pair == IND_CODE) ? (byte_pair = T_IND) : 0;
		if (!(byte_pair & op_tab[command - 1].type_arg[i]))
			return (1);
		i++;
	}
	return (0);
}

int			get_args(t_data *data, t_bot *bot)
{
	char			i;
	char			arg_type;
	char			offset;
	unsigned char	*map;

	i = 0;
	offset = 0;
	map = data->map + bot->pc;
	while (i < op_tab[bot->command - 1].n_arg)
	{
		arg_type = get_arg_type(bot->command, bot->opcode, i + 1);
		if (arg_type == REG_CODE)
		{
			bot->args[i] = get_number_from_bcode(map + offset, 1);
			if (bot->args[i] > REG_NUMBER || bot->args[i] < 1)
				return (1);
			offset += 1;
		}
		else if (arg_type == DIR_CODE && op_tab[bot->command - 1].dir_as_label)
		{
			bot->args[i] = get_number_from_bcode(map + offset, IND_SIZE);
			offset += IND_SIZE;
		}
		else if (arg_type == DIR_CODE)
		{
			bot->args[i] = get_number_from_bcode(map + offset, DIR_SIZE);
			offset += DIR_SIZE;
		}
		else if (arg_type == IND_CODE)
		{
			bot->args[i] = get_number_from_bcode(map + offset, IND_SIZE);
			offset += IND_SIZE;
		}
		else
			return (1);
		i++;
	}
	return (0);
}
