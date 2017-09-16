#include "commands.h"

int			arithmetic_operations(t_data *data, t_bot *bot)
{
	if (bot->command == 4)
		bot->reg[bot->args[2]] =
				bot->reg[bot->args[0]] + bot->reg[bot->args[1]];
	else
		bot->reg[bot->args[2]] =
				bot->reg[bot->args[0]] - bot->reg[bot->args[1]];
	(bot->reg[bot->args[2]] == 0) ? (bot->carry = 1) :
		(bot->carry = 0);
	return (0);
}

int			logic_operations(t_data *data, t_bot *bot)
{
	int		i;
	int		num[2];
	char	arg_type;

	i = 0;
	while (i < g_tab[bot->command - 1].n_arg - 1)
	{
		arg_type = get_arg_type(bot->command, bot->opcode, i + 1);
		if (arg_type == REG_CODE)
			num[i] = bot->reg[bot->args[i]];
		else if (arg_type == DIR_CODE)
			num[i] = bot->reg[bot->args[i]];
		else if (arg_type == IND_CODE)
			num[i] = get_number_from_bcode(data->map +
					(bot->pc + (bot->args[i] % IDX_MOD) + MEM_SIZE)
										% MEM_SIZE, DIR_SIZE);
		i++;
	}
	(bot->command == 6) ? (bot->reg[bot->args[2]] = num[0] & num[1]) : 0;
	(bot->command == 7) ? (bot->reg[bot->args[2]] = num[0] | num[1]) : 0;
	(bot->command == 8) ? (bot->reg[bot->args[2]] = num[0] ^ num[1]) : 0;
	if (bot->args[2] >= 1 && bot->args[2] <= 16)
		(bot->reg[bot->args[2]] == 0) ? (bot->carry = 1) :
			(bot->carry = 0);
	return (0);
}

int			st_command(t_data *data, t_bot *bot)
{
	put_number_to_bcode(data, bot->reg[bot->args[0]], ((bot->pc +
			(bot->args[1] % IDX_MOD) + MEM_SIZE) % MEM_SIZE));
	(data->visual) ? (ncurses_change_memory(((bot->pc +
			(bot->args[1] % IDX_MOD)) + MEM_SIZE) % MEM_SIZE,
											bot, data)) : 0;
	return (0);
}

int			sti_command(t_data *data, t_bot *bot)
{
	if (get_arg_type(bot->command, bot->opcode, 2) == IND_CODE)
		bot->args[1] = get_number_from_bcode(data->map + (bot->pc + 2 +
				(bot->args[1] % IDX_MOD) + MEM_SIZE) % MEM_SIZE, IND_SIZE);
	else if (get_arg_type(bot->command, bot->opcode, 2) == REG_CODE)
		bot->args[1] = bot->reg[bot->args[1]] % IDX_MOD;
	else
		bot->args[1] = bot->args[1] % IDX_MOD;
	if (get_arg_type(bot->command, bot->opcode, 3) == REG_CODE)
		bot->args[2] = bot->reg[bot->args[2]] % IDX_MOD;
	else
		bot->args[2] = bot->args[2] % IDX_MOD;
	put_number_to_bcode(data, bot->reg[bot->args[0]], ((bot->pc +
			((bot->args[1] + bot->args[2]) % IDX_MOD) + MEM_SIZE) % MEM_SIZE));
	(data->visual) ? (ncurses_change_memory(((bot->pc +
			((bot->args[1] + bot->args[2]) % IDX_MOD)) + MEM_SIZE) % MEM_SIZE,
											bot, data)) : 0;
	return (0);
}

int			st_operations(t_data *data, t_bot *bot)
{
	if (bot->command == 3)
		st_command(data, bot);
	else
		sti_command(data, bot);
	return (0);
}

int			ld_lld_commands(t_data *data, t_bot *bot)
{
	if (get_arg_type(bot->command, bot->opcode, 1) == DIR_CODE)
		bot->reg[bot->args[1]] = bot->args[0];
	else if (bot->command == 2 &&
			(get_arg_type(bot->command, bot->opcode, 1) == IND_CODE))
		bot->reg[bot->args[1]] = get_number_from_bcode(data->map +
		(bot->pc + (bot->args[0] % IDX_MOD) + MEM_SIZE) % MEM_SIZE, DIR_SIZE);
	else if (bot->command == 13 &&
			(get_arg_type(bot->command, bot->opcode, 1) == IND_CODE))
		bot->reg[bot->args[1]] = get_number_from_bcode(data->map +
				(bot->pc + bot->args[0] + MEM_SIZE) % MEM_SIZE, DIR_SIZE);
	return (0);
}

void		ldi_lldi_commands(t_data *data, t_bot *bot)
{
	int		a[2];

	if (get_arg_type(bot->command, bot->opcode, 1) == REG_CODE)
		a[0] = bot->reg[bot->args[0]];
	else if (get_arg_type(bot->command, bot->opcode, 1) == DIR_CODE)
		a[0] = bot->args[0];
	else if (bot->command == 10 &&
			(get_arg_type(bot->command, bot->opcode, 1) == IND_CODE))
		a[0] = (get_number_from_bcode(data->map + (bot->pc + 2 +
				(bot->args[0] % IDX_MOD) + MEM_SIZE) % MEM_SIZE, IND_SIZE));
	else if (bot->command == 14 && (get_arg_type(bot->command,
												bot->opcode, 1) == IND_CODE))
		a[0] = (get_number_from_bcode(data->map + (bot->pc + 2 +
				(bot->args[0]) + MEM_SIZE) % MEM_SIZE, IND_SIZE));
	if (get_arg_type(bot->command, bot->opcode, 2) == REG_CODE)
		(bot->command == 10) ? (a[1] = bot->reg[bot->args[1]] % IDX_MOD) :
		(a[1] = bot->reg[bot->args[1]]);
	else if (get_arg_type(bot->command, bot->opcode, 2) == DIR_CODE)
		a[1] = bot->args[1];
	if (bot->command == 10)
		bot->reg[bot->args[2]] = get_number_from_bcode(data->map +
		(bot->pc + ((a[0] + a[1]) % IDX_MOD) + MEM_SIZE) % MEM_SIZE, DIR_SIZE);
	else
		bot->reg[bot->args[2]] = get_number_from_bcode(data->map +
		(bot->pc + (a[0] + a[1]) + MEM_SIZE) % MEM_SIZE, DIR_SIZE);
}

int			ld_operations(t_data *data, t_bot *bot)
{
	if (bot->command == 2 || bot->command == 13)
	{
		ld_lld_commands(data, bot);
		(bot->reg[bot->args[1]] == 0) ? (bot->carry = 1) :
			(bot->carry = 0);
	}
	else
	{
		ldi_lldi_commands(data, bot);
		(bot->reg[bot->args[2]] == 0 &&
			bot->command == 14) ? (bot->carry = 1) :
			(bot->carry = 0);
	}
	return (0);
}

int			fork_operations(t_data *data, t_bot *bot)
{
	t_bot	*child;

	child = bot_copy(bot);
	if (bot->command == 12)
		child->pc = ((bot->pc + (bot->args[0] % IDX_MOD)) + MEM_SIZE)
					% MEM_SIZE;
	else if (bot->command == 15)
		child->pc = ((bot->pc + bot->args[0]) + MEM_SIZE) % MEM_SIZE;
	child->prev_live = -1;
	child->pause_time = 0;
	data->bots_tail = list_append_to_tail(&(data->bots_tail), child);
	(data->visual) ? (ncurses_move_cursor(data, child, child->pc)) : 0;
	data->processes[bot->number]++;
	return (0);
}

int			live_operation(t_data *data, t_bot *bot)
{
	bot->throw_live = 1;
	if (bot->r1_number == bot->args[0])
	{
		bot->live_count++;
		bot->last_live = data->cycles;
		data->bots_live[bot->number]++;
		data->bots_last_live[bot->number] = data->cycles;
		if (data->visual)
			ncurses_live(data, bot);
		else
			(data->debug_level - LIVE_LEVEL >= 0) ?
			(ft_printf("A process shows that player %d (%s) is alive\n",
					bot->number, data->bots_names[bot->number])) : 0;
	}
	else if (ABS(bot->args[0]) >= 1 && ABS(bot->args[0]) <= MAX_PLAYERS + 1
			&& bot->args[0] < 0)
	{
		data->bots_live[ABS(bot->args[0])]++;
		data->bots_last_live[ABS(bot->args[0])] = data->cycles;
	}
	else
		data->bots_live[0]++;
	return (0);
}

int			zjmp_operation(t_data *data, t_bot *bot)
{
	if (bot->carry == 1)
		bot->pc = ((bot->pc + (bot->args[0] % IDX_MOD) + MEM_SIZE) % MEM_SIZE);
	else
		bot->pc = (bot->pc + 1 + IND_SIZE) % MEM_SIZE;
	return (0);
}

int			aff_operation(t_data *data, t_bot *bot)
{
	if (data->visual)
		ncurses_aff(data, bot, bot->args[0]);
	else
		ft_printf("Player %d: reg[%d] = %d '%c'\n",
				bot->number, bot->args[0], bot->reg[bot->args[0]],
				(bot->reg[bot->args[0]] >= 32
				&& bot->reg[bot->args[0]] <= 126) ?
				(bot->reg[bot->args[0]]) : (32));
	return (0);
}

int			run_command(t_data *data, t_bot *bot)
{
	int		ret;

	ret = 0;
	if (bot->command == 4 || bot->command == 5)
		ret = arithmetic_operations(data, bot);
	else if (bot->command == 6 || bot->command == 7 || bot->command == 8)
		ret = logic_operations(data, bot);
	else if (bot->command == 3 || bot->command == 11)
		ret = st_operations(data, bot);
	else if (bot->command == 2 || bot->command == 10 || bot->command == 13
			|| bot->command == 14)
		ret = ld_operations(data, bot);
	else if (bot->command == 12 || bot->command == 15)
		ret = fork_operations(data, bot);
	else if (bot->command == 1)
		ret = live_operation(data, bot);
	else if (bot->command == 9)
		ret = zjmp_operation(data, bot);
	else if (bot->command == 16)
		ret = aff_operation(data, bot);
	return (ret);
}

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

static int	norm1(t_bot *bot, t_data *data, int *prev)
{
	bot->opcode = data->map[bot->pc];
	bot->pc = (bot->pc + 1) % MEM_SIZE;
	if (check_opcode(bot->command, bot->opcode))
	{
		(data->visual) ? (ncurses_move_cursor(data, bot, *prev)) : 0;
		return (1);
	}
	return (0);
}

static int	norm2(t_bot *bot, t_data *data, int *prev)
{
	bot->pc = (bot->pc + 1) % MEM_SIZE;
	(data->visual) ? (ncurses_move_cursor(data, bot, *prev)) : 0;
	return (1);
}

static int	norm3(t_bot *bot, t_data *data, int *prev)
{
	*prev = bot->pc;
	bot->pc = (bot->pc + 1) % MEM_SIZE;
	if (g_tab[bot->command - 1].have_opcode)
		if (norm1(bot, data, prev))
			return (1);
	if (get_args(data, bot))
		return (norm2(bot, data, prev));
	bot->pc--;
	(g_tab[bot->command - 1].have_opcode) ? (bot->pc--) : 0;
	if (run_command(data, bot))
	{
		(bot->command != 9) ?
		(increase_pc(bot, bot->command, bot->opcode)) : 0;
		(data->visual) ? (ncurses_move_cursor(data, bot, *prev)) : 0;
		return (1);
	}
	(bot->command != 9) ? (increase_pc(bot, bot->command, bot->opcode)) : 0;
	return (0);
}

int			execute_command(t_data *data, t_bot *bot)
{
	int		prev;

	bot->opcode = 0;
	ft_bzero(bot->args, 3 * sizeof(int));
	bot->command = data->map[bot->pc];
	prev = bot->pc;
	if (bot->command >= 1 && bot->command <= 16)
	{
		if (norm3(bot, data, &prev))
			return (1);
	}
	else
		return (norm2(bot, data, &prev));
	(data->visual) ? (ncurses_move_cursor(data, bot, prev)) : 0;
	return (0);
}

int			first_pause(t_data *data)
{
	t_linked_list	*curr;
	t_bot			*bot;

	curr = data->bots;
	data->pause_time = 2147483647;
	while (curr)
	{
		bot = curr->data;
		if (((data->map[bot->pc]) >= 1) && ((data->map[bot->pc]) <= 16))
			bot->pause_time = g_tab[data->map[bot->pc] - 1].cycles_to_done;
		else
			bot->pause_time = 0;
		(data->pause_time > bot->pause_time) ?
				(data->pause_time = bot->pause_time) : 0;
		curr = curr->next;
	}
	return (0);
}

static void	set_bot_pause_time(t_data *data, t_bot *bot)
{
	if (((data->map[bot->pc]) <= 16) && ((data->map[bot->pc]) >= 1))
		bot->pause_time = g_tab[data->map[bot->pc] - 1].cycles_to_done;
	else
		bot->pause_time = 1;
}

/*
** 0 - ok , 1 - error
*/

int			execute_commands(t_data *data, int min)
{
	t_linked_list	*curr;
	t_bot			*bot;

	curr = data->bots;
	while (curr && (bot = curr->data))
	{
		if (!bot->is_dead)
		{
			if (!bot->is_dead && ((bot->pause_time - data->pause_time) <= 0) &&
				(bot->pause_time != 0))
			{
				execute_command(data, bot);
				set_bot_pause_time(data, bot);
			}
			else if (!bot->is_dead && (bot->pause_time == 0))
				set_bot_pause_time(data, bot);
			else if (!bot->is_dead)
				bot->pause_time -= data->pause_time;
		}
		(min > bot->pause_time && !bot->is_dead) ? (min = bot->pause_time) : 0;
		curr = curr->next;
	}
	data->pause_time = (min == 0) ? (1) : (min);
	return (0);
}
