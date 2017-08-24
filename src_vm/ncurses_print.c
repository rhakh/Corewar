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

	i = 3;
	while (i < 15)
	{
		wattron(data->debug_win, COLOR_PAIR(bot->number) | A_REVERSE);
		mvwprintw(data->debug_win, i++, 4, "%62s", ".");
		wattroff(data->debug_win, COLOR_PAIR(bot->number) | A_REVERSE);
	}
	wrefresh(data->debug_win);
	refresh();
}