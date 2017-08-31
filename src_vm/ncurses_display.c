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
			print_byte(win, data->map[i], i, COLOR_PAIR(12));
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
		wattron(stats_win, COLOR_PAIR(9) | A_BOLD);
		mvwprintw(stats_win, 1, 25, "*** PAUSED ***");
		wattroff(stats_win, COLOR_PAIR(9) | A_BOLD);
	}
	else
		mvwprintw(stats_win, 1, 25, "*** RUNNING **");
	ncurses_speed_display(data);
	mvwprintw(stats_win, 7, 3, "%-10s %-11d", "Cycle:",  data->cycles);
	mvwprintw(stats_win, 8, 3, "%-10s %-11d", "Processes:", data->processes);
	wmove(stats_win, 10, 3);
	n_bot = -1;
	while (++n_bot < data->bots_count)
	{
		wprintw(stats_win, "Player-%d: ", n_bot + 1);
		wattron(stats_win, COLOR_PAIR(cur_bot->number + 5) | A_BOLD);
		wprintw(stats_win, "%.55s", cur_bot->name);
		wattroff(stats_win, COLOR_PAIR(cur_bot->number + 5) | A_BOLD);
		getyx(stats_win, y, x);
		mvwprintw(stats_win, y + 1, 10, "Live in current period: %-11d", data->bots_live[n_bot + 1]);
		mvwprintw(stats_win, y + 2, 10, "Last live             : %-11d", data->bots_last_live[n_bot + 1]);

		// for the next players
		list = list->next;
		list ? cur_bot = list->data : 0;
		!list ? cur_bot = NULL : 0;
		getyx(stats_win, y, x);
		wmove(stats_win, y + 2, 3);
	}
	getyx(stats_win, y, x);
	mvwprintw(stats_win, y + 2, 6, "%-13s: %4d", "CYCLES_TO_DIE", data->cycles_to_die);
	mvwprintw(stats_win, y + 3, 6, "%-13s: %4d", "CYCLE_DELTA", CYCLE_DELTA);
	mvwprintw(stats_win, y + 4, 6, "%-13s: %4d", "NBR_LIVE", NBR_LIVE);
	mvwprintw(stats_win, y + 5, 6, "%-13s: %4d", "MAX_CHECKS", MAX_CHECKS);
	wrefresh(stats_win);
}

void		display_debug(t_data *data, WINDOW *debug_win)
{
	int 	x;
	int 	y;

	wattron(debug_win, COLOR_PAIR(5) | A_REVERSE);
	mvwprintw(debug_win, 1, 28, "DEBUG WIN");
	wattroff(debug_win, COLOR_PAIR(5) | A_REVERSE);
	wrefresh(debug_win);
}

void		display_winner(t_data *data, t_bot *bot)
{
	wattron(data->stats_win, COLOR_PAIR(bot->number));
	mvwprintw(data->stats_win, 45, 10, "The winner is");
	wattron(data->stats_win, COLOR_PAIR(bot->number + 5) | A_BOLD );
	mvwprintw(data->stats_win, 45, 25, "%s", bot->name);
	wattroff(data->stats_win, COLOR_PAIR(bot->number) |
			COLOR_PAIR(bot->number + 5));
	mvwprintw(data->stats_win, 47, 25, "Type q to exit");
	wrefresh(data->stats_win);
	refresh();
	(data->visual) ? 0 : (ft_printf("{green}The winner is '%s'\n{eoc}", bot->name));
}

void		ncurses_speed_display(t_data *data)
{
	int 	speed;
	int 	i;

	speed = ncurses_convert_speed(data);
	mvwprintw(data->stats_win, 6, 3, "%s", "Speed: |");
	i = 1;
	while (speed-- > 0)
	{
		wattron(data->stats_win, COLOR_PAIR(13));
		wprintw(data->stats_win, "%s", "*");
		wattroff(data->stats_win, COLOR_PAIR(13));
		i++;
	}
	while (i++ <= 12)
	{
		wattron(data->stats_win, COLOR_PAIR(11));
		wprintw(data->stats_win, "%s", "*");
		wattroff(data->stats_win, COLOR_PAIR(11));
	}
	wprintw(data->stats_win, "|");
	wattron(data->stats_win, COLOR_PAIR(12));
	wprintw(data->stats_win, "%5sA<->S - decrease<->increase", " ");
	wattroff(data->stats_win, COLOR_PAIR(12));

}

int 	ncurses_convert_speed(t_data *data)
{
	int		speed;

	data->ncurses_timeout == 0 ? speed = 12 : 0;
	data->ncurses_timeout == 1 ? speed = 11 : 0;
	data->ncurses_timeout == 2 ? speed = 10 : 0;
	data->ncurses_timeout == 4 ? speed = 9 : 0;
	data->ncurses_timeout == 8 ? speed = 8 : 0;
	data->ncurses_timeout == 16 ? speed = 7 : 0;
	data->ncurses_timeout == 32 ? speed = 6 : 0;
	data->ncurses_timeout == 64 ? speed = 5 : 0;
	data->ncurses_timeout == 128 ? speed = 4 : 0;
	data->ncurses_timeout == 256 ? speed = 3 : 0;
	data->ncurses_timeout == 512 ? speed = 2 : 0;
	data->ncurses_timeout == 1024 ? speed = 1 : 0;
	return (speed);
}