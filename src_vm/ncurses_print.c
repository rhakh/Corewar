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
	if (bot->prev_live != -1)
		while (i <= 0)
		{
			print_byte(data->memory_win, data->map[(bot->prev_live + i +
													MEM_SIZE) % MEM_SIZE ],
					   (bot->prev_live + i + MEM_SIZE) % MEM_SIZE,
					   COLOR_PAIR(bot->number));
			i++;
		}
	i = 0;
	while (i <= 0)
	{
		print_byte(data->memory_win, data->map[(bot->pc + i + MEM_SIZE) %
											   MEM_SIZE],
				   (bot->pc + i + MEM_SIZE) % MEM_SIZE,
				   COLOR_PAIR(bot->number + 5) | A_BOLD);
		i++;
	}
	bot->prev_live = bot->pc;
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
	ft_snprintf(data->debug_strs[0], 61, "Player %d: reg[%d] = %d '%c'", bot->number, nb_reg, bot->reg[nb_reg], (char)bot->reg[nb_reg]);
	line = 3;
	i = 0;
	while (i < 12)
		mvwprintw(data->debug_win, line++, 4, " %s", data->debug_strs[i++]);
	wrefresh(data->debug_win);
	refresh();
}