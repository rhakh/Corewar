#include "pause_time.h"

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

void		set_bot_pause_time(t_data *data, t_bot *bot)
{
	if (((data->map[bot->pc]) <= 16) && ((data->map[bot->pc]) >= 1))
		bot->pause_time = g_tab[data->map[bot->pc] - 1].cycles_to_done;
	else
		bot->pause_time = 1;
}
