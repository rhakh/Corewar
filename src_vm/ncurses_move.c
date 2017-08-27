//
// Created by Serhii Bondar on 8/13/17.
//

#include <curses.h>
#include <ncurses.h>
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
			print_byte(data->memory_win, data->map[(bot->prev_st + i + MEM_SIZE)
												   % MEM_SIZE], (bot->prev_st +
					i + MEM_SIZE) % MEM_SIZE, COLOR_PAIR(bot->number));
	}
	i = -1;
	while (++i < len)
		print_byte(data->memory_win, data->map[(start + i + MEM_SIZE) %
											   MEM_SIZE], (start + i + MEM_SIZE)
														  % MEM_SIZE,
				   COLOR_PAIR(bot->number) | A_BOLD);
	bot->prev_st = start;
	return (0);
}

/*
 * Applies move cursor effect.
 */
int 		ncurses_move_cursor(t_data *data, t_bot *bot, int prev)
{
	chtype character;
	int 	x;
	int 	y;

	wrefresh(data->memory_win);
	move_to_byte(data->memory_win, bot->pc);
	getyx(data->memory_win, y, x);
	character = mvwinch(data->memory_win, y, x);
	if (character & A_REVERSE)
		character = character ^ A_REVERSE;
	if (bot->prev_attr)
	bot->prev_attr == -1 ? bot->prev_attr = COLOR_PAIR(bot->number) : 0;
	print_byte(data->memory_win, data->map[prev], prev, bot->prev_attr);
	print_byte(data->memory_win, data->map[bot->pc], bot->pc, character |
																  A_REVERSE);
	bot->prev_attr = character;
	return (0);
}

/*
 * Moves window cursor to given byte.
 */
void		move_to_byte(WINDOW *win, int byte) {
	int size = ft_sqrt(MEM_SIZE);
	wmove(win, byte / size + 1, byte % size * 2 + byte % size + 1);
}
