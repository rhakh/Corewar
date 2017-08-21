#include "commands.h"

int 		arithmetic_operations(t_bot *bot, char command, int args[3])
{
	if (command == 4)
		bot->reg[args[2]] = bot->reg[args[0]] + bot->reg[args[1]];
	else
		bot->reg[args[2]] = bot->reg[args[0]] - bot->reg[args[1]];
	bot->pause_time = op_tab[command - 1].cycles_to_done;
	return (0);
}

int 		logic_operations(t_data *data, t_bot *bot, char command, char opcode, int args[3])
{
	int 	i;
	int 	num[2];
	char 	arg_type;

	i = 0;
	while (i < op_tab[command - 1].n_arg - 1)
	{
		arg_type = get_arg_type(opcode, i + 1);
		if (arg_type == REG_CODE)
			num[i] = bot->reg[args[i]];
		else if (arg_type == DIR_CODE)
			num[i] = bot->reg[args[i]];
		else if (arg_type == IND_CODE)
			num[i] = get_number_from_bcode(data->map + (bot->pc + (args[i] % IDX_MOD)), DIR_SIZE);
		i++;
	}
	(command == 6) ? (bot->reg[args[2]] = num[0] & num[1]) : 0;
	(command == 7) ? (bot->reg[args[2]] = num[0] | num[1]) : 0;
	(command == 8) ? (bot->reg[args[2]] = num[0] ^ num[1]) : 0;
	return (0);
}

int 		st_operations(t_data *data, t_bot *bot, char command, char opcode, int args[3])
{
	if (command == 3)
		put_number_to_bcode(data, bot->reg[args[0]], (bot->pc + (args[1] % IDX_MOD)));
	if (command == 11)
		put_number_to_bcode(data, bot->reg[args[0]], (bot->pc + ((args[1] + args[2]) % IDX_MOD)));
//todo sbondar
//	if (send_to_ncurses((bot->pc + ((args[1] + IDX_MOD) % IDX_MOD)), DIR_SIZE, bot, data))
//		return (1);
//	maybe better to name this function like 'update_bytes_ncurses' or 'update_bytes_nc' ...
	return (0);
}

int 		ld_operations(t_data *data, t_bot *bot, char command, char opcode, int args[3])
{
	int 	addr[2];

	if (command == 2)
	{
		if (get_arg_type(opcode, 1) == DIR_CODE)
			bot->reg[args[1]] = args[0];
		else if (get_arg_type(opcode, 1) == IND_CODE)
			bot->reg[args[1]] = get_number_from_bcode(data->map + (bot->pc + (args[0] % IDX_MOD)), 4);
		else
			return (1);
	}
	else if (command == 10)
	{
		if (get_arg_type(opcode, 1) == REG_CODE)
			addr[0] = bot->reg[args[0]];
		else if (get_arg_type(opcode, 1) == DIR_CODE)
			addr[0] = args[0];
		else if (get_arg_type(opcode, 1) == IND_CODE)
			addr[0] = (short)(get_number_from_bcode(data->map + (bot->pc + (args[0] % IDX_MOD)), 2));
		else
			return (1);

		if (get_arg_type(opcode, 2) == REG_CODE)
			addr[1] = bot->reg[args[1]];
		else if (get_arg_type(opcode, 2) == DIR_CODE)
			addr[1] = args[1];
		else
			return (1);

		bot->reg[args[2]] = get_number_from_bcode(data->map + (bot->pc + (addr[0] + addr[1] % IDX_MOD)), 4);
	}
	else if (command == 13)
	{
		if (get_arg_type(opcode, 1) == DIR_CODE)
			bot->reg[args[1]] = args[0];
		else if (get_arg_type(opcode, 1 == IND_CODE))
			bot->reg[args[1]] = get_number_from_bcode(data->map + (bot->pc + args[0]), 4);//todo test it, 4 replace to 2
	}
	else if (command == 14)
	{
		if (get_arg_type(opcode, 1) == REG_CODE)
			addr[0] = bot->reg[args[0]];
		else if (get_arg_type(opcode, 1) == DIR_CODE)
			addr[0] = args[0];
		else if (get_arg_type(opcode, 1) == IND_CODE)
			addr[0] = (short)(get_number_from_bcode(data->map + (bot->pc + (args[0])), 2));
		else
			return (1);

		if (get_arg_type(opcode, 2) == REG_CODE)
			addr[1] = bot->reg[args[1]];
		else if (get_arg_type(opcode, 2) == DIR_CODE)
			addr[1] = args[1];
		else
			return (1);

		bot->reg[args[2]] = get_number_from_bcode(data->map + (bot->pc + (addr[0] + addr[1])), 4);
	}
	return (0);
}

int 		fork_operations(t_data *data, t_bot * bot, char command, char opcode, int args[3])
{
	
	return (0);
}

int 		live_operation(t_data *data, t_bot *bot, char command, char opcode, int args[3])
{
	//todo
	return (0);
}

int 		zjmp_operation(t_data *data, t_bot *bot, char command, char opcode, int args[3])
{
	//todo
	return (0);
}

int 		aff_operation(t_data *data, t_bot *bot, char command, char opcode, int args[3])
{
	//todo
	return (0);
}

int 		run_command(t_data *data, t_bot *bot, char command, char opcode, int args[3])
{
	if (command == 4 || command == 5)
		arithmetic_operations(bot, command, args);
	if (command == 6 || command == 7 || command == 8)
		logic_operations(data, bot, command, opcode, args);
	if (command == 3 || command == 11)
		st_operations(data, bot, command, opcode, args);
	if (command == 2 || command == 10 || command == 13 || command == 14)
		ld_operations(data, bot, command, opcode, args);
	if (command == 12 || command == 15)
		fork_operations(data, bot, command, opcode, args);
	if (command == 1)
		live_operation(data, bot, command, opcode, args);
	if (command == 9)
		zjmp_operation(data, bot, command, opcode, args);
	if (command == 16)
		aff_operation(data, bot, command, opcode, args);
	return (0);
}

int 		increase_pc(t_bot *bot, char comand, char opcode)
{
	int 	offset;
	int 	i;

	i = 0;
	offset = 0;
	offset++;
	if (op_tab[comand - 1].have_opcode)
		offset++;
	while (i < op_tab[comand - 1].n_arg)
	{
		if (get_arg_type(opcode, i + 1) == REG_CODE)
			offset++;
		else if (get_arg_type(opcode, i + 1) == DIR_CODE)
		{
			if (op_tab[comand - 1].dir_as_label)
				offset += 2;
			else
				offset += 4;
		}
		else if (get_arg_type(opcode, i + 1) == IND_CODE)
			offset += 2;
		if (comand == 1)
			offset += 4;
		else if (comand == 9 || comand == 12 || comand == 15)
			offset += 2;
		i++;
	}
	(offset == 0) ? (offset = 1) : 0;
	bot->pc += offset;
	return (0);
}

int 		execute_command(t_data *data, t_bot *bot)
{
	char 			command;
	char 			opcode;
	int 			args[3];
	int 			prev;

	opcode = 0;
	command = data->map[bot->pc];
	prev = bot->pc;
	bot->pc++;
	if (op_tab[command - 1].have_opcode)
	{
		opcode = data->map[bot->pc];
		bot->pc++;
	}

	if (get_args(data, bot, command, opcode, args))
		return (1);

	bot->pc--;
	if (op_tab[command - 1].have_opcode)
		bot->pc--;

	if (run_command(data, bot, command, opcode, args))
		return (1);

	bot->pause_time = op_tab[command - 1].cycles_to_done;
	increase_pc(bot, command, opcode);
	ft_printf("{red}prev = %d crr %d\n{eoc}", prev, bot->pc);
	//todo send past and current cursor pos
	//todo ncurses move_curcor
	//todo ncurses ncurses_move_cursor(bot, prev)

	return (0);
}

/*
** 0 - ok , 1 - error
*/
int 		execute_commands(t_data *data)
{
	//todo hakh
	t_linked_list	*curr;
	t_bot			*bot;
	int 			min;

	min = 2147483647;
	curr = data->bots;
	while (curr)
	{
		bot = curr->data;
		if (min > bot->pause_time)
			min = bot->pause_time;
		curr = curr->next;
	}
	curr = data->bots;
	while (curr)
	{
		bot = curr->data;
		if (min == bot->pause_time)
		{
			if (execute_command(data, bot))
				return (1);
		}
		else
			bot->pause_time -= min;
		curr = curr->next;
	}
	data->cycles += min;
	return (0);
}
