//
// Created by Serhii Bondar on 8/13/17.
//

#include <curses.h>
#include "vm.h"

/*
 * len no need
 */
int			ncurses_change_memory(int start, int len, t_bot *bot, t_data *data)
{
	int i;

	i = -1;
	if (bot->prev_st != -1)
	{
		while (++i < len)
			print_byte(data->memory_win, data->map[bot->prev_st + i],
					   bot->prev_st + i, COLOR_PAIR(bot->number));
	}
	i = -1;
	while (++i < len)
		print_byte(data->memory_win, data->map[start + i], start + i,
				   COLOR_PAIR(bot->number) | A_BOLD);
	bot->prev_st = start;
	return (0);
}

/*
 * Applies move cursor effect.
 * TODO: get atribute, then A_REVERSE
 */
int 		ncurses_move_cursor(t_data *data, t_bot *bot, int prev)
{
//	wattr_get(data->memory_win, ***, ***, ***);
	print_byte(data->memory_win, data->map[prev], prev, COLOR_PAIR(bot->number));
	print_byte(data->memory_win, data->map[bot->pc], bot->pc, COLOR_PAIR(bot->number) | A_REVERSE);
	return (0);
}

/*
 * Moves window cursor to given byte.
 */
void		move_to_byte(WINDOW *win, int byte) {
	int size = ft_sqrt(MEM_SIZE);
	wmove(win, byte / size + 1, byte % size * 2 + byte % size + 1);
}
