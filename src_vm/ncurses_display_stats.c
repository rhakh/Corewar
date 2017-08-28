/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_display_stats.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtelega <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 19:29:18 by dtelega           #+#    #+#             */
/*   Updated: 2017/08/28 20:23:33 by dtelega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		display_stats(t_data *data, WINDOW *stats_win)
{
	int				n_bot;
	t_bot			*cur_bot;
	t_linked_list	*list;

	list = data->bots;
	cur_bot = (t_bot *)list->data;
	if (data->pause)
	{
		wattron(stats_win, COLOR_PAIR(9) | A_BOLD);
		mvwprintw(stats_win, 1, 25, "*** PAUSED ***");
		wattroff(stats_win, COLOR_PAIR(9) | A_BOLD);
	}
	else
		mvwprintw(stats_win, 1, 25, "*** RUNNING **");
	display_curr_speed_cycles(data, stats_win);
	wmove(stats_win, 10, 3);
	n_bot = -1;
	while (++n_bot < data->bots_count)
	{
		display_players(data, stats_win, cur_bot, n_bot);
		list = list->next;
		list ? cur_bot = list->data : 0;
		!list ? cur_bot = NULL : 0;
	}
	display_defines(data, stats_win);
}

void		display_players(t_data *data, WINDOW *stats_win, t_bot *cur_bot,
							int n_bot)
{
	int		x;
	int		y;

	wprintw(stats_win, "Player-%d: ", n_bot + 1);
	wattron(stats_win, COLOR_PAIR(cur_bot->number + 5) | A_BOLD);
	wprintw(stats_win, "%.55s", cur_bot->name);
	wattroff(stats_win, COLOR_PAIR(cur_bot->number + 5) | A_BOLD);
	getyx(stats_win, y, x);
	mvwprintw(stats_win, y + 1, 10, "Live in current period: %4d",
			data->bots_live[n_bot + 1]);
	mvwprintw(stats_win, y + 2, 10, "Last live             : %4d",
			data->bots_last_live[n_bot + 1]);
	getyx(stats_win, y, x);
	wmove(stats_win, y + 2, 3);
}

void		display_defines(t_data *data, WINDOW *stats_win)
{
	int x;
	int y;

	getyx(stats_win, y, x);
	mvwprintw(stats_win, y + 2, 6, "%-13s: %4d", "CYCLES_TO_DIE",
			data->cycles_to_die);
	mvwprintw(stats_win, y + 3, 6, "%-13s: %4d", "CYCLE_DELTA", CYCLE_DELTA);
	mvwprintw(stats_win, y + 4, 6, "%-13s: %4d", "NBR_LIVE", NBR_LIVE);
	mvwprintw(stats_win, y + 5, 6, "%-13s: %4d", "MAX_CHECKS", MAX_CHECKS);
	wrefresh(stats_win);
}

void		display_curr_speed_cycles(t_data *data, WINDOW *stats_win)
{
	int		speed;
	int		i;

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
	mvwprintw(stats_win, 7, 3, "%-10s %6d", "Cycle:", data->cycles);
	mvwprintw(stats_win, 8, 3, "%-10s %6d", "Processes:", data->processes);
}

int			ncurses_convert_speed(t_data *data)
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
