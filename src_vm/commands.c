#include "commands.h"

int 		arithmetic_operations(t_bot *bot, char command, int args[3])
{
	if (command == 4)
		bot->reg[args[2]] = bot->reg[args[0]] + bot->reg[args[1]];
	else
		bot->reg[args[2]] = bot->reg[args[0]] - bot->reg[args[1]];
	(bot->reg[args[2]] == 0) ? (bot->carry = 1) : (bot->carry = 0);
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
		arg_type = get_arg_type(command, opcode, i + 1);
		if (arg_type == REG_CODE)
			num[i] = bot->reg[args[i]];
		else if (arg_type == DIR_CODE)
			num[i] = bot->reg[args[i]];
		else if (arg_type == IND_CODE)
			num[i] = get_number_from_bcode(data->map + (bot->pc + (args[i] % IDX_MOD) + MEM_SIZE) % MEM_SIZE, DIR_SIZE);
		i++;
	}
	(command == 6) ? (bot->reg[args[2]] = num[0] & num[1]) : 0;
	(command == 7) ? (bot->reg[args[2]] = num[0] | num[1]) : 0;
	(command == 8) ? (bot->reg[args[2]] = num[0] ^ num[1]) : 0;
	(bot->reg[args[2]] == 0) ? (bot->carry = 1) : (bot->carry = 0);
	return (0);
}

int 		st_operations(t_data *data, t_bot *bot, char command, char opcode, int args[3])
{
	if (command == 3)
		put_number_to_bcode(data, bot->reg[args[0]], ((bot->pc + (args[1] % IDX_MOD) + MEM_SIZE) % MEM_SIZE));
	else
	{
		if (get_arg_type(command, opcode, 2) == IND_CODE)
			args[1] = get_number_from_bcode(data->map + (bot->pc + 2 + (args[1] % IDX_MOD) + MEM_SIZE) % MEM_SIZE, IND_SIZE);
		else if (get_arg_type(command, opcode, 2) == REG_CODE)
			args[1] = bot->reg[args[1]] % IDX_MOD;
		else
			args[1] = args[1] % IDX_MOD;

		if (get_arg_type(command, opcode, 3) == REG_CODE)
			args[2] = bot->reg[args[2]] % IDX_MOD;
		else
			args[2] = args[2] % IDX_MOD;

		put_number_to_bcode(data, bot->reg[args[0]], ((bot->pc + ((args[1] + args[2]) % IDX_MOD) + MEM_SIZE) % MEM_SIZE));
	}

	if (command == 3)
		ncurses_change_memory(((bot->pc + (args[1] % IDX_MOD)) + MEM_SIZE) % MEM_SIZE, DIR_SIZE, bot, data);
	else
		ncurses_change_memory(((bot->pc + ((args[1] + args[2]) % IDX_MOD)) + MEM_SIZE) % MEM_SIZE, DIR_SIZE, bot, data);

	return (0);
}

int 		ld_operations(t_data *data, t_bot *bot, char command, char opcode, int args[3])
{
	int 	addr[2];

	if (command == 2 || command == 13)
	{
		if (get_arg_type(command, opcode, 1) == DIR_CODE)
			bot->reg[args[1]] = args[0];
		else if (command == 2 && (get_arg_type(command, opcode, 1) == IND_CODE))
			bot->reg[args[1]] = get_number_from_bcode(data->map + (bot->pc + (args[0] % IDX_MOD) + MEM_SIZE) % MEM_SIZE, DIR_SIZE);
		else if (command == 13 && (get_arg_type(command, opcode, 1) == IND_CODE))
			bot->reg[args[1]] = get_number_from_bcode(data->map + (bot->pc + args[0] + MEM_SIZE) % MEM_SIZE, DIR_SIZE);
		else
			return (1);
		(bot->reg[args[1]] == 0) ? (bot->carry = 1) : (bot->carry = 0);
	}
	else if (command == 10 || command == 14)
	{
		if (get_arg_type(command, opcode, 1) == REG_CODE)
			addr[0] = bot->reg[args[0]];
		else if (get_arg_type(command, opcode, 1) == DIR_CODE)
			addr[0] = args[0];
		else if (command == 10 && (get_arg_type(command, opcode, 1) == IND_CODE))
			addr[0] = (get_number_from_bcode(data->map + (bot->pc + 2 + (args[0] % IDX_MOD) + MEM_SIZE) % MEM_SIZE, IND_SIZE)); //del 2
		else if (command == 14 && (get_arg_type(command, opcode, 1) == IND_CODE))
			addr[0] = (get_number_from_bcode(data->map + (bot->pc + 2 + (args[0]) + MEM_SIZE) % MEM_SIZE, IND_SIZE));

		if (get_arg_type(command, opcode, 2) == REG_CODE)
			(command == 10) ? (addr[1] = bot->reg[args[1]] % IDX_MOD) : (addr[1] = bot->reg[args[1]]);
		else if (get_arg_type(command, opcode, 2) == DIR_CODE)
			addr[1] = args[1];

		if (command == 10)
			bot->reg[args[2]] = get_number_from_bcode(data->map + (bot->pc + ((addr[0] + addr[1]) % IDX_MOD) + MEM_SIZE) % MEM_SIZE, DIR_SIZE);
		else
			bot->reg[args[2]] = get_number_from_bcode(data->map + (bot->pc + (addr[0] + addr[1]) + MEM_SIZE) % MEM_SIZE, DIR_SIZE);
		(bot->reg[args[2]] == 0 && command == 14) ? (bot->carry = 1) : (bot->carry = 0);
	}
	return (0);
}

int 		fork_operations(t_data *data, t_bot * bot, char command, char opcode, int args[3])
{
	t_bot	*child;

	child = bot_copy(bot);
	if (command == 12)
		child->pc = ((bot->pc + (args[0] % IDX_MOD)) + MEM_SIZE) % MEM_SIZE;
	else if (command == 15)
		child->pc = ((bot->pc + args[0]) + MEM_SIZE) % MEM_SIZE;
	child->prev_live = -1;
	child->pause_time = 0;
	list_push_back(&(data->bots), child);
	data->processes++;
	return (0);
}

int 		live_operation(t_data *data, t_bot *bot, char command, char opcode, int args[3])
{
	t_linked_list	*curr;
	t_bot			*curr_bot;

	curr = data->bots;
	bot->throw_live = 1;
	if (bot->number == ABS(args[0]))
	{
		bot->live_count++;
		bot->last_live = data->cycles;
		data->bots_live[bot->number]++;
		data->bots_last_live[bot->number] = data->cycles;
		ncurses_live(data, bot); // ncurses print pointer
		return (0);
	}
	while (curr)
	{
		curr_bot = curr->data;
		if (curr_bot->number == ABS(args[0]))
		{
			curr_bot->live_count++;
			curr_bot->last_live = data->cycles;
			data->bots_live[curr_bot->number]++;
			data->bots_last_live[curr_bot->number] = data->cycles;
			ncurses_live(data, curr_bot);
			return (0);
		}
		curr = curr->next;
	}
	return (1);
}

int 		zjmp_operation(t_data *data, t_bot *bot, char command, char opcode, int args[3])
{
	if (bot->carry == 1)
		bot->pc = ((bot->pc + (args[0] % IDX_MOD) + MEM_SIZE) % MEM_SIZE);
	else
		bot->pc += 1 + IND_SIZE;
	return (0);
}

int 		aff_operation(t_data *data, t_bot *bot, char command, char opcode, int args[3])
{
	//todo send to ncurses bot, reg_number
	ncurses_aff(data, bot, args[0]); //args[0] - numberof register to display
	return (0);
}

int 		run_command(t_data *data, t_bot *bot, char command, char opcode, int args[3])
{
	int 	ret;

	ret = 0;
	if (command == 4 || command == 5)
		ret = arithmetic_operations(bot, command, args);
	else if (command == 6 || command == 7 || command == 8)
		ret = logic_operations(data, bot, command, opcode, args);
	else if (command == 3 || command == 11)
		ret = st_operations(data, bot, command, opcode, args);
	else if (command == 2 || command == 10 || command == 13 || command == 14)
		ret = ld_operations(data, bot, command, opcode, args);
	else if (command == 12 || command == 15)
		ret = fork_operations(data, bot, command, opcode, args);
	else if (command == 1)
		ret = live_operation(data, bot, command, opcode, args);
	else if (command == 9)
		ret = zjmp_operation(data, bot, command, opcode, args);
	else if (command == 16)
		ret = aff_operation(data, bot, command, opcode, args);
	return (ret);
}

int 		increase_pc(t_bot *bot, char command, char opcode)
{
	int 	offset;
	int 	i;

	i = 0;
	offset = 0;
	offset++;
	if (op_tab[command - 1].have_opcode)
		offset++;
	while (i < op_tab[command - 1].n_arg)
	{
		if (get_arg_type(command, opcode, i + 1) == REG_CODE)
			offset++;
		else if (get_arg_type(command, opcode, i + 1) == DIR_CODE)
		{
			if (op_tab[command - 1].dir_as_label)
				offset += 2;
			else
				offset += 4;
		}
		else if (get_arg_type(command, opcode, i + 1) == IND_CODE)
			offset += 2;
		else
			offset++;
		i++;
	}
	(offset == 0) ? (offset = 1) : 0;
	bot->pc = (bot->pc + offset) % MEM_SIZE;
	return (0);
}

//int 		execute_command(t_data *data, t_bot *bot)
//{
//	char 			command;
//	char 			opcode;
//	int 			args[3];
//	int 			prev;
//
//	opcode = 0;
//	command = data->map[bot->pc];
//	prev = bot->pc;
//	if (command >= 1 && command <= 16)
//	{
//		if (bot->pause_time == - 1)
//		{
//			bot->pause_time = op_tab[command - 1].cycles_to_done - 2;
//			return (0);
//		}
//		prev = bot->pc;
//		bot->pc++;
//		if (op_tab[command - 1].have_opcode)
//		{
//			opcode = data->map[bot->pc];
//			bot->pc++;
//		}
//
//		if (get_args(data, bot, command, opcode, args))
//		{
//			bot->pause_time = -1;
//			bot->pc = (bot->pc + 1) % MEM_SIZE;
//			ncurses_move_cursor(data, bot, prev);
//			return (1);
//		}
//
//		bot->pc--;
//		if (op_tab[command - 1].have_opcode)
//			bot->pc--;
//
//		if (run_command(data, bot, command, opcode, args))
//		{
//			bot->pause_time = -1;
//			(command != 9) ? (increase_pc(bot, command, opcode)) : (bot->pc += 1 + IND_SIZE);
//			ncurses_move_cursor(data, bot, prev);
//			return (1);
//		}
//
//		bot->pause_time = -1;
//		(command != 9) ? (increase_pc(bot, command, opcode)) : 0;
//	}
//	else
//	{
//		bot->pc = (bot->pc + 1) % MEM_SIZE;
//		bot->pause_time = 0;
//	}
//	//todo send past and current cursor pos
//	//todo ncurses move_curcor
//	//todo ncurses ncurses_move_cursor(bot, prev)
//
//	ncurses_move_cursor(data, bot, prev);
//	return (0);
//}

int 		execute_command(t_data *data, t_bot *bot)
{
	char 			command;
	char 			opcode;
	int 			args[3];
	int 			prev;

	opcode = 0;
	command = data->map[bot->pc];
	prev = bot->pc;
	if (command >= 1 && command <= 16)
	{
		prev = bot->pc;
		bot->pc++;
		if (op_tab[command - 1].have_opcode)
		{
			opcode = data->map[bot->pc];
			bot->pc++;
		}

		if (get_args(data, bot, command, opcode, args))
		{
			bot->pc = (bot->pc + 1) % MEM_SIZE;
			ncurses_move_cursor(data, bot, prev);
			return (1);
		}

		bot->pc--;
		if (op_tab[command - 1].have_opcode)
			bot->pc--;

		if (run_command(data, bot, command, opcode, args))
		{
			(command != 9) ? (increase_pc(bot, command, opcode)) : (bot->pc += 1 + IND_SIZE);
			ncurses_move_cursor(data, bot, prev);
			return (1);
		}

		(command != 9) ? (increase_pc(bot, command, opcode)) : 0;
	}
	else
	{
		bot->pc = (bot->pc + 1) % MEM_SIZE;
		ncurses_move_cursor(data, bot, prev);
		return (1);
	}
	ncurses_move_cursor(data, bot, prev);
	return (0);
}

int 		check_for_live_bots(t_data *data)
{
	t_linked_list	*curr;
	t_bot			*bot;
	int 			sum_live;

	sum_live = 0;
	curr = data->bots;
	while (curr)
	{

		bot = curr->data;
		sum_live += bot->live_count;
		if (bot->last_live > 0 && ((data->cycles - bot->last_live) > data->cycles_to_die) && bot->is_dead == 0)
		{
			bot->is_dead = 1;
			(data->processes > 0) ? (data->processes--) : 0;
		}
		else
		{
			data->bots_live[bot->number] = 0;
			bot->live_count = 0;
			bot->throw_live = 0;
		}
		curr = curr->next;
	}
	if (sum_live >= NBR_LIVE)
		(data->cycles_to_die - CYCLE_DELTA > 0) ? (data->cycles_to_die -= CYCLE_DELTA) : (data->cycles_to_die = 0);
	return (0);
}

int 		first_pause(t_data *data)
{
	t_linked_list	*curr;
	t_bot			*bot;

	curr = data->bots;
	while (curr)
	{
		bot = curr->data;
		if (((data->map[bot->pc] - 1) >= 1) && ((data->map[bot->pc] - 1) <= 16))
			bot->pause_time = op_tab[data->map[bot->pc] - 1].cycles_to_done;
		else
			bot->pause_time = 0;
		curr = curr->next;
	}
	return (0);
}

/*
** 0 - ok , 1 - error
*/
int 		execute_commands(t_data *data)
{
	t_linked_list	*curr;
	t_bot			*bot;

	curr = data->bots;
	while (curr)
	{
		bot = curr->data;
		if (bot->is_dead == 0 && bot->pause_time == 0)
		{
			if (execute_command(data, bot))
				bot->pause_time = 0;
			else
				bot->pause_time = op_tab[data->map[bot->pc] - 1].cycles_to_done - 1;
		}
		else
			bot->pause_time -= 1;
		curr = curr->next;
	}

	if (data->cycles > 0 && (data->cycles == data->next_cycles_check))
	{
		check_for_live_bots(data);
		data->next_cycles_check = data->cycles + data->cycles_to_die;
		data->max_checks++;
		if (data->max_checks > 0 && (data->max_checks % MAX_CHECKS == 0))
		{
			if (data->last_cycles_to_die == data->cycles_to_die)
			{
				data->cycles_to_die -= CYCLE_DELTA;
				data->next_cycles_check = data->cycles + data->cycles_to_die;
			}
			data->last_cycles_to_die = data->cycles_to_die;
		}
	}

	data->cycles += 1;

	return (0);
}
