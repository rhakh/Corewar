#include "pc_adder.h"

int			increase_pc(t_bot *bot, char command, char opcode)
{
	int		offset;
	int		i;

	i = -1;
	offset = 0;
	offset++;
	(g_tab[command - 1].have_opcode) ? (offset++) : 0;
	while (++i < g_tab[command - 1].n_arg)
	{
		if (get_arg_type(command, opcode, i + 1) == REG_CODE)
			offset++;
		else if (get_arg_type(command, opcode, i + 1) == DIR_CODE)
			(g_tab[command - 1].dir_as_label) ? (offset += 2) :
			(offset += 4);
		else if (get_arg_type(command, opcode, i + 1) == IND_CODE)
			offset += 2;
		else
			offset++;
	}
	(offset == 0) ? (offset = 1) : 0;
	bot->pc = (bot->pc + offset) % MEM_SIZE;
	return (0);
}
