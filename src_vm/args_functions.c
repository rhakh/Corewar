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
	while (i < g_tab[command - 1].n_arg)
	{
		byte_pair = (unsigned char)((opcode >> (6 - (2 * i))) & 0b00000011);
		(byte_pair == REG_CODE) ? (byte_pair = T_REG) : 0;
		(byte_pair == DIR_CODE) ? (byte_pair = T_DIR) : 0;
		(byte_pair == IND_CODE) ? (byte_pair = T_IND) : 0;
		if (!(byte_pair & g_tab[command - 1].type_arg[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	stupid_norms(int *i, t_bot *bot, int *o, t_data *d)
{
	if (get_arg_type(bot->command, bot->opcode, *i + 1) == REG_CODE)
	{
		bot->args[*i] = get_number_from_bcode(d->map + bot->pc + *o, 1);
		if ((*o += 1) && (bot->args[*i] > REG_NUMBER || bot->args[*i] < 1))
			return (1);
	}
	else if (get_arg_type(bot->command, bot->opcode, *i + 1) == DIR_CODE &&
			g_tab[bot->command - 1].dir_as_label)
	{
		bot->args[*i] = get_number_from_bcode(d->map + bot->pc + *o, IND_SIZE);
		*o += IND_SIZE;
	}
	else if (get_arg_type(bot->command, bot->opcode, *i + 1) == DIR_CODE)
	{
		bot->args[*i] = get_number_from_bcode(d->map + bot->pc + *o, DIR_SIZE);
		*o += DIR_SIZE;
	}
	else if (get_arg_type(bot->command, bot->opcode, *i + 1) == IND_CODE)
	{
		bot->args[*i] = get_number_from_bcode(d->map + bot->pc + *o, IND_SIZE);
		*o += IND_SIZE;
	}
	else
		return (1);
	return (0);
}

int			get_args(t_data *data, t_bot *bot)
{
	int				i;
	int				offset;

	i = 0;
	offset = 0;
	while (i < g_tab[bot->command - 1].n_arg)
	{
		if (stupid_norms(&i, bot, &offset, data))
			return (1);
		i++;
	}
	return (0);
}
