/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 16:45:08 by rhakh             #+#    #+#             */
/*   Updated: 2017/09/16 16:45:09 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialization.h"

void			load_bots_in_memory(t_data *data)
{
	t_linked_list	*curr;
	t_bot			*curr_bot;
	int				period;
	int				i;
	int				bot_number;

	i = 0;
	bot_number = 1;
	period = MEM_SIZE / data->bots_count;
	curr = data->bots;
	while (curr)
	{
		curr_bot = curr->data;
		curr_bot->reg[1] = -1 * bot_number;
		curr_bot->r1_number = -1 * bot_number;
		curr_bot->number = bot_number;
		curr_bot->pc = i;
		curr_bot->start = i;
		data->processes[curr_bot->number]++;
		ft_memcpy(data->map + i, curr_bot->code->str +
			16 + PROG_NAME_LENGTH + COMMENT_LENGTH, (size_t)curr_bot->size);
		i += period;
		curr = curr->next;
		bot_number++;
	}
}

static void		dummy_norm(t_bot *bot, t_data *data)
{
	bot->last_live = 0;
	bot->is_dead = 0;
	bot->prev_attr = -1;
	data->bots_tail = list_push_back(&(data->bots), bot);
}

/*
** 0 - ok, 1 - error
*/

int				init_bots(t_data *data, char *argv[MAX_PLAYERS + 1], int num)
{
	int			i;
	int			ret;
	t_string	*curr;
	t_bot		*bot;

	i = 0;
	ret = 0;
	while (++i < (MAX_PLAYERS + 1) && i < (num + 1) && (curr = string_new(30)))
	{
		(read_bot(curr, argv[i])) ? (ret = 1) : 0;
		(bot = bot_new(i + 1, curr)) ? 0 :
		(ret = 1);
		if (ret)
		{
			string_del(&curr);
			return (1);
		}
		dummy_norm(bot, data);
	}
	if (validate_bots(data) || data->bots_count == 0)
	{
		(data->bots_count == 0) ? (ft_printf("{red}Bots count = 0\n{eoc}")) : 0;
		return (1);
	}
	return (0);
}

/*
** 0 - ok, 1 - error
*/

int				infinit_loop(t_data *data)
{
	int		next_command;

	next_command = data->pause_time - 1;
	while (data->cycles_to_die > 0 && sum_processes(data) > 0)
	{
		if (data->visual)
			ncurses_visual(data);
		if (!data->pause || data->one_command_mode)
			next_command = process_bots_commands(data, next_command);
		if (data->visual)
		{
			display_stats(data, data->stats_win);
			wrefresh(data->memory_win);
			refresh();
		}
	}
	return (0);
}

int				process_bots_commands(t_data *data, int next_command)
{
	(data->dump == data->cycles && !data->visual) ? (print_dump(data)) : 0;
	if (data->cycles == data->next_cycles_check)
	{
		check_for_live_bots(data);
		data->next_cycles_check = data->cycles + data->cycles_to_die;
		if ((data->max_checks++ > 0) && (data->max_checks % MAX_CHECKS == 0))
		{
			if (data->last_cycles_to_die == data->cycles_to_die)
			{
				(data->cycles_to_die - CYCLE_DELTA > 0) ?
				(data->cycles_to_die -= CYCLE_DELTA) :
				(data->cycles_to_die = 0);
				data->next_cycles_check = data->cycles + data->cycles_to_die;
			}
			data->last_cycles_to_die = data->cycles_to_die;
		}
	}
	if (next_command <= 0)
	{
		if (execute_commands(data, 2147483647))
			return (1);
		next_command = data->pause_time;
	}
	data->cycles++;
	return (next_command - 1);
}
