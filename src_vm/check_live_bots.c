#include "check_live_bots.h"

static void		code_in_loop(t_bot *bot, t_data *data)
{
	if (!bot->throw_live &&
		((data->cycles - bot->last_live) >= data->cycles_to_die) &&
		!bot->is_dead)
	{
		bot->is_dead = 1;
		(data->processes[bot->number] > 0) ?
		(data->processes[bot->number]--) : 0;
		(data->visual) ? (ncurses_kill_bot_cursor(data, bot->pc)) : 0;
		if (data->processes[bot->number] == 0)
			(data->visual && !data->mute) ? (sdl_sound(MUS_DEAD)) : 0;
		(!data->visual && data->debug_level - LIVE_LEVEL >= 0) ?
		(ft_printf("Player %d (%s) is dead\n",
				bot->number, data->bots_names[bot->number])) : 0;
	}
	else
	{
		data->bots_live[bot->number] = 0;
		bot->live_count = 0;
		bot->throw_live = 0;
	}
}

int				check_for_live_bots(t_data *data)
{
	t_linked_list	*curr;
	t_bot			*bot;
	int				sum_live;

	sum_live = data->bots_live[0];
	curr = data->bots;
	while (curr)
	{
		bot = curr->data;
		sum_live += bot->live_count;
		code_in_loop(bot, data);
		curr = curr->next;
	}
	if (sum_live >= NBR_LIVE)
		(data->cycles_to_die - CYCLE_DELTA > 0) ?
		(data->cycles_to_die -= CYCLE_DELTA) : (data->cycles_to_die = 0);
	data->bots_live[0] = 0;
	return (0);
}
