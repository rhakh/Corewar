/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 16:44:53 by rhakh             #+#    #+#             */
/*   Updated: 2017/09/16 16:44:54 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands_manager.h"

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
