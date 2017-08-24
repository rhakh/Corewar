#include "vm.h"

void	display_memory(t_data *data, WINDOW *win)
{
	int i;
	int x;
	int y;
	t_bot   *cur_bot;
	t_linked_list   *list;

	i = -1;
	list = data->bots;
	cur_bot = (t_bot *)list->data;
	while (++i < MEM_SIZE)
	{
		// *перенос строчки
		if (i % ft_sqrt(MEM_SIZE) == 0) {
			getyx(win, y, x);
			wmove(win, y + 1, 1);
		}
		// *печать с цветом бота
		if (cur_bot && i == cur_bot->pc)
		{

			int j = 0;
			// *print start cursor
			print_byte(win, data->map[i], i, COLOR_PAIR(cur_bot->number) |
											 A_REVERSE);
			i++;
			while (++j < cur_bot->size)
			{
				print_byte(win, data->map[i], i, COLOR_PAIR(cur_bot->number));
				if (++i % ft_sqrt(MEM_SIZE) == 0 && j + 1 != cur_bot->size)
				{
					getyx(win, y, x);
					wmove(win, y + 1, 1);
				}
			}
			list = list->next;
			list ? cur_bot = list->data : 0;
			!list ? cur_bot = NULL : 0;
			i--;
		}
		else
			wprintw(win, "%0.2hhx ", data->map[i]); // *print grey 00
	}
	wrefresh(win);
}

void		display_stats(t_data *data, WINDOW *stats_win)
{
	int 	n_bot;
	int 	x;
	int 	y;
	t_bot   *cur_bot;
	t_linked_list   *list;

	list = data->bots;
	cur_bot = (t_bot *)list->data;
	/* if data->pause == 0 then PAUSE, else RUNNING */
	if (data->pause)
	{
		wattron(stats_win, COLOR_PAIR(10));
		mvwprintw(stats_win, 1, 28, "*** PAUSE ***");
		wattroff(stats_win, COLOR_PAIR(10));
	}
	else
		mvwprintw(stats_win, 1, 28, "** RUNNING **");
	mvwprintw(stats_win, 6, 3, "%-10s %6d", "Cycle:", /* count of cycles here */ data->cycles);
	mvwprintw(stats_win, 7, 3, "%-10s %6d", "Processes:", /* count of processes here*/ data->processes);
	wmove(stats_win, 10, 3);
	n_bot = -1;
	while (++n_bot < data->bots_count)
	{
		wprintw(stats_win, "Player-%d: ", n_bot + 1);
		wattron(stats_win, COLOR_PAIR(n_bot + 1) | A_REVERSE);
		wprintw(stats_win, "%.55s", cur_bot->name);
		wattroff(stats_win, COLOR_PAIR(n_bot + 1) | A_REVERSE);
		getyx(stats_win, y, x);
		mvwprintw(stats_win, y + 1, 10, "Live in current period: %4d", data->bots_live[n_bot]);
		mvwprintw(stats_win, y + 2, 10, "Last live             : %4d", data->bots_last_live[n_bot]);

		// for the next players
		list = list->next;
		list ? cur_bot = list->data : 0;
		!list ? cur_bot = NULL : 0;
		getyx(stats_win, y, x);
		wmove(stats_win, y + 2, 3);
	}
	getyx(stats_win, y, x);
	mvwprintw(stats_win, y + 2, 6, "%13s: %4d", "CYCLES_TO_DIE", data->cycles_to_die);
	mvwprintw(stats_win, y + 3, 6, "%13s: %4d", "CYCLE_DELTA", CYCLE_DELTA);
	mvwprintw(stats_win, y + 4, 6, "%13s: %4d", "NBR_LIVE", NBR_LIVE);
	mvwprintw(stats_win, y + 5, 6, "%13s: %4d", "MAX_CHECKS", MAX_CHECKS);
	wrefresh(stats_win);
}

void		display_debug(t_data *data, WINDOW *debug_win)
{
	int 	x;
	int 	y;

	wattron(debug_win, COLOR_PAIR(10));
	mvwprintw(debug_win, 1, 28, "DEBUG WIN");
	wattroff(debug_win, COLOR_PAIR(10));

	getyx(debug_win, y, x);
	mvwprintw(debug_win, y + 2, 10, "try ./corewar -hui_znaet_chto to use debug options");

	wrefresh(debug_win);
}
