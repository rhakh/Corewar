/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 16:46:21 by rhakh             #+#    #+#             */
/*   Updated: 2017/09/16 16:46:22 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int			arithmetic_operations(t_bot *bot)
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
		data->bots_last_live[bot->number] = data->cycles + 1;
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
		data->bots_last_live[ABS(bot->args[0])] = data->cycles + 1;
	}
	else
		data->bots_live[0]++;
	return (0);
}

int			zjmp_operation(t_bot *bot)
{
	if (bot->carry == 1)
		bot->pc = ((bot->pc + (bot->args[0] % IDX_MOD) + MEM_SIZE) % MEM_SIZE);
	else
		bot->pc = (bot->pc + 1 + IND_SIZE) % MEM_SIZE;
	return (0);
}
