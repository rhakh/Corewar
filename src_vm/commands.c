#include "commands.h"

int 		arithmetic_operations(t_data *data, t_bot *bot, char command, char opcode, int args[3])
{
	int 	i;

	i = -1;
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
	if (args[2] >= 1 && args[2] <= 16)
		(bot->reg[args[2]] == 0) ? (bot->carry = 1) : (bot->carry = 0);
	i = 0;
	return (0);
}

int 		st_operations(t_data *data, t_bot *bot, char command, char opcode, int args[3])
{
	int 	i;

	i = 0;
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
		(data->visual) ? (ncurses_change_memory(((bot->pc + (args[1] % IDX_MOD)) + MEM_SIZE) % MEM_SIZE, DIR_SIZE, bot, data)) : 0;
	else
		(data->visual) ? (ncurses_change_memory(((bot->pc + ((args[1] + args[2]) % IDX_MOD)) + MEM_SIZE) % MEM_SIZE, DIR_SIZE, bot, data)) : 0;
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
//	list_push_back(&(data->bots), child); //add tail to the linked list to increase speed
	data->bots_tail = list_append_to_tail(&(data->bots_tail), child);
	(data->visual) ? (ncurses_move_cursor(data, child, child->pc)) : 0;
	data->processes[bot->number]++;
	return (0);
}

int 		live_operation(t_data *data, t_bot *bot, char command, char opcode, int args[3])
{
	t_linked_list	*curr;
	t_bot			*curr_bot;

	curr = data->bots;
	bot->throw_live = 1;
	if (bot->r1_number == args[0])
	{
		bot->live_count++;
		bot->last_live = data->cycles;
		data->bots_live[bot->number]++;
		data->bots_last_live[bot->number] = data->cycles;
		if (data->visual)
			ncurses_live(data, bot);
		else
			(data->debug_level - LIVE_LEVEL >= 0) ? (ft_printf("A process shows that player %d (%s) is alive\n", bot->number, data->bots_names[bot->number])) : 0;
		return (0);
	}
	else if (ABS(args[0]) >= 1 && ABS(args[0]) <= MAX_PLAYERS + 1 && args[0] < 0)
	{
		data->bots_live[ABS(args[0])]++;
		data->bots_last_live[ABS(args[0])] = data->cycles;
	}
	else
		data->bots_live[0]++;
	return (0);
}

int 		zjmp_operation(t_data *data, t_bot *bot, char command, char opcode, int args[3])
{
	if (bot->carry == 1)
		bot->pc = ((bot->pc + (args[0] % IDX_MOD) + MEM_SIZE) % MEM_SIZE);
	else
		bot->pc = (bot->pc + 1 + IND_SIZE) % MEM_SIZE;
	return (0);
}

int 		aff_operation(t_data *data, t_bot *bot, char command, char opcode, int args[3])
{
	if (data->visual)
		ncurses_aff(data, bot, args[0]); //args[0] - number of register to display
	else
		ft_printf("Player %d: reg[%d] = %d '%c'\n",
				  bot->number, args[0], bot->reg[args[0]],
				  (bot->reg[args[0]] >= 32 && bot->reg[args[0]] <= 126) ?
				  (bot->reg[args[0]]) : (32));
	return (0);
}

int 		run_command(t_data *data, t_bot *bot, char command, char opcode, int args[3])
{
	int 	ret;

	ret = 0;
	if (command == 4 || command == 5)
		ret = arithmetic_operations(data, bot, command, opcode, args);
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

int 		command_size(char command, char opcode)
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
	return (offset);
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

	if (command >= 1 && command <= 16)
	{
		prev = bot->pc;
		bot->pc++;
		if (op_tab[command - 1].have_opcode)
		{
			opcode = data->map[bot->pc];
			bot->pc++;
			if (check_opcode(command, opcode))
			{
				(data->visual) ? (ncurses_move_cursor(data, bot, prev)) : 0;
				return (1);
			}
		}
		if (get_args(data, bot, command, opcode, args))
		{
			bot->pc = (bot->pc + 1) % MEM_SIZE;
			(data->visual) ? (ncurses_move_cursor(data, bot, prev)) : 0;
			return (1);
		}
		bot->pc--;
		if (op_tab[command - 1].have_opcode)
			bot->pc--;

		if (run_command(data, bot, command, opcode, args))
		{
			(command != 9) ? (increase_pc(bot, command, opcode)) : 0;
			(data->visual) ? (ncurses_move_cursor(data, bot, prev)) : 0;
			return (1);
		}

		(command != 9) ? (increase_pc(bot, command, opcode)) : 0;
	}
	else
	{
		bot->pc = (bot->pc + 1) % MEM_SIZE;
		(data->visual) ? (ncurses_move_cursor(data, bot, prev)) : 0;
		return (1);
	}
	(data->visual) ? (ncurses_move_cursor(data, bot, prev)) : 0;
	return (0);
}

int 		check_for_live_bots(t_data *data)
{
	t_linked_list	*curr;
	t_bot			*bot;
	int 			sum_live;

	sum_live = data->bots_live[0];
	curr = data->bots;
	while (curr)
	{
		bot = curr->data;
		sum_live += bot->live_count;
		if (!bot->throw_live && ((data->cycles - bot->last_live) >= data->cycles_to_die) && !bot->is_dead)
		{
			bot->is_dead = 1;
			(data->processes[bot->number] > 0) ? (data->processes[bot->number]--) : 0;
			(data->visual) ? (ncurses_kill_bot_cursor(data, bot->pc)) : 0;
			if (data->processes[bot->number] == 0)
				(data->visual && !data->mute) ? (sdl_sound(MUS_DEAD)) : 0;
			(!data->visual && data->debug_level - LIVE_LEVEL >= 0) ? (ft_printf("Player %d (%s) is dead\n", bot->number, data->bots_names[bot->number])) : 0;
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
	data->bots_live[0] = 0;
	return (0);
}

int 		first_pause(t_data *data)
{
	t_linked_list	*curr;
	t_bot			*bot;

	curr = data->bots;
	data->pause_time = 2147483647;
	while (curr)
	{
		bot = curr->data;
		if (((data->map[bot->pc]) >= 1) && ((data->map[bot->pc]) <= 16))
			bot->pause_time = op_tab[data->map[bot->pc] - 1].cycles_to_done;
		else
			bot->pause_time = 0;
		(data->pause_time > bot->pause_time) ? (data->pause_time = bot->pause_time) : 0;
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
	int 			min;

	curr = data->bots;
	min = 2147483647;
	while (curr)
	{
		bot = curr->data;
		if ((bot->is_dead == 0) && ((bot->pause_time - data->pause_time) <= 0) && (bot->pause_time != 0))
		{
			if (execute_command(data, bot))
				bot->pause_time = 1;
			else if (((data->map[bot->pc]) <= 16) && ((data->map[bot->pc]) >= 1))
				bot->pause_time = op_tab[data->map[bot->pc] - 1].cycles_to_done;
			else
				bot->pause_time = 1;
		}
		else if ((bot->is_dead == 0) && (bot->pause_time == 0))
		{
			if (((data->map[bot->pc]) <= 16) && ((data->map[bot->pc]) >= 1))
				bot->pause_time = op_tab[data->map[bot->pc] - 1].cycles_to_done;
			else
				bot->pause_time = 1;
		}
		else if (bot->is_dead == 0)
			bot->pause_time -= data->pause_time;
		(min > bot->pause_time && !bot->is_dead) ? (min = bot->pause_time) : 0;
		curr = curr->next;
	}
	(min == 0) ? (data->pause_time = 1) : (data->pause_time = min);
	return (0);
}


