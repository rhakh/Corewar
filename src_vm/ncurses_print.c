#include "vm.h"
//
// Created by Dmytro Telega on 8/19/17.
//

void		print_byte(WINDOW *win, char byte, int position, int attr)
{
	move_to_byte(win, position);
	wattron(win, attr);
	wprintw(win, "%0.2hhx", byte);
	wattroff(win, attr);
	wprintw(win, " ");
}

void		ncurses_live(t_data *data, t_bot *bot)
{
	int 	i;

	i = 0;
	if (bot->prev_curr_live[0] != -1)
		while (i <= 4)
		{
			print_byte(data->memory_win, data->map[bot->prev_curr_live[0] + i],
					   bot->prev_curr_live[0] + i, COLOR_PAIR(bot->number));
			i++;
		}
	i = 0;
	while (i <= 4)
	{
		print_byte(data->memory_win, data->map[bot->prev_curr_live[1] + i],
				   bot->prev_curr_live[1] + i, COLOR_PAIR(bot->number) | A_REVERSE | A_BOLD);
		i++;
	}
	wrefresh(data->memory_win);
	refresh();
}

void 		ncurses_aff(t_data *data, t_bot *bot, int nb_reg)
{
	int 	i;
	int 	k;
	int 	line;

	i = 10;
	while (i >= 0)
	{
		k = 0;
		while (k < 61)
		{
			data->debug_strs[i + 1][k] = data->debug_strs[i][k];
			k++;
		}
		i--;
	}
	line = 3;
	while (i < 12)
	{
		wattron(data->debug_win, COLOR_PAIR(bot->number) | A_REVERSE);
		mvwprintw(data->debug_win, line++, 4, "%62s", data->debug_strs[i++]);
		wattroff(data->debug_win, COLOR_PAIR(bot->number) | A_REVERSE);
	}
	wrefresh(data->debug_win);
	refresh();
}