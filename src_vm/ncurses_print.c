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